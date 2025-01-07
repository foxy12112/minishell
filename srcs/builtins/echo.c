/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:05 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/06 17:09:33 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char *args, int fd, bool n_option)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putchar_fd(args[i], fd);
		i++;
	}
	if (!n_option)
	{
		ft_putchar_fd('\n', fd);
	}
	free(args);
	return (0);
}

static bool	has_anything(char **command)
{
	if (!command[1])
		return (false);
	return (true);
}

char	*true_quote_removal(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = ft_strlen_s(str, '\"') + 1;
	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !str[i + 1])
			break ;
		if (str[i] == '"')
		{
			i++;
			continue ;
		}
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	parse_launch_echo(char **command)
{
	bool	has_n_option;
	char	*echo_string;

	has_n_option = false;
	if (has_anything(command) == false)
		return (ft_putchar_fd('\n', 1), 1);
	if (ft_strcmp(command[1], "-n") == 0)
		has_n_option = true;
	if (has_n_option)
		echo_string = join_arof_ars(command, 2);
	else
		echo_string = join_arof_ars(command, 1);
	echo_string = true_quote_removal(echo_string);
	ft_echo(echo_string, STDOUT_FILENO, has_n_option);
	return (0);
}
