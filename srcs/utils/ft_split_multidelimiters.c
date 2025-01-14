/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multidelimiters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 03:16:19 by macbook           #+#    #+#             */
/*   Updated: 2025/01/14 01:28:03 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_split_state
{
	int					str_idx;
	int					buffer_idx;
	int					result_idx;
	char				**result;
	char				*buffer;
	bool				found_exit_code;
}						t_split_state;

typedef struct s_memblock
{
	void				*address;
	struct s_memblock	*next;
}						t_memblock;

t_memblock	**ft_gc_get(void)
{
	static t_memblock	*head;

	return (&head);
}

void	ft_free(void *address)
{
	t_memblock	**head;
	t_memblock	*prev;
	t_memblock	*next;

	head = ft_gc_get();
	prev = NULL;
	next = *head;
	while (next != NULL)
	{
		if (next->address == address)
		{
			if (prev == NULL)
				*head = next->next;
			else
				prev->next = next->next;
			free(next->address);
			free(next);
			return ;
		}
		prev = next;
		next = next->next;
	}
}

static void	ft_handle_split(t_split_state *state, char *str)
{
	state->found_exit_code = false;
	state->buffer[state->buffer_idx] = '\0';
	if (state->buffer_idx != 0)
		state->result[state->result_idx++] = ft_strdup(state->buffer);
	state->buffer_idx = 0;
	while (str[state->str_idx] == '\'' || str[state->str_idx] == '\"'
		|| str[state->str_idx] == ' ')
	{
		state->buffer[state->buffer_idx] = str[state->str_idx];
		state->buffer[++state->buffer_idx] = '\0';
		state->result[state->result_idx++] = ft_strdup(state->buffer);
		state->buffer_idx = 0;
		state->str_idx++;
	}
	if (str[state->str_idx] != '\0')
	{
		state->buffer[state->buffer_idx] = str[state->str_idx];
		state->buffer_idx++;
	}
	state->str_idx++;
}

bool	is_exit_code(char *str, int idx)
{
	if (idx - 1 < 0)
		return (false);
	if ((str[idx] == '?' && str[idx - 1] == '$') || (str[idx] == '/' && str[idx
			- 1] == '$'))
		return (true);
	return (false);
}

static t_split_state	*ft_init_split_state(const char *str)
{
	t_split_state	*state;

	state = malloc(sizeof(t_split_state));
	if (!state)
		return (NULL);
	state->result = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	if (!state->result)
	{
		ft_free(state);
		return (NULL);
	}
	state->buffer = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!state->buffer)
	{
		ft_free(state->result);
		ft_free(state);
		return (NULL);
	}
	state->str_idx = 0;
	state->result_idx = 0;
	state->buffer_idx = 0;
	state->found_exit_code = false;
	return (state);
}

bool	is_delimiter1(char c)
{
	return (!ft_isalnum(c) && c != '_' && c != '*');
}

bool	is_delimiter(char c)
{
	if(c == '"' || c == '\'')
		return (true);
	return (false);
	// return (!ft_isalnum(c) && c != '_' && c != '*');
}

char	**ft_split_multidelimiter(const char *str, bool(delim)(char c))
{
	t_split_state *state;

	state = ft_init_split_state(str);
	while ((size_t)state->str_idx < (size_t)ft_strlen(str)
		&& str[state->str_idx] != '\0')
	{
		if ((!delim(str[state->str_idx]) || is_exit_code((char *)str,
					state->str_idx)) && !state->found_exit_code)
		{
			if (is_exit_code((char *)str, state->str_idx))
				state->found_exit_code = true;
			state->buffer[state->buffer_idx++] = str[state->str_idx++];
		}
		else
			ft_handle_split(state, (char *)str);
	}
	if (state->buffer_idx != 0)
	{
		state->buffer[state->buffer_idx] = '\0';
		state->result[state->result_idx++] = ft_strdup(state->buffer);
	}
	ft_free(state->buffer);
	state->result[state->result_idx] = NULL;
	return (state->result);
}