/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:08:24 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/17 11:55:29 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!str[i])
			break ;
		free(str[i]);
		i++;
	}
	free(str);
}

char	**free_all(char **parentarray, int arrayindex)
{
	int	j;

	j = 0;
	while (j < arrayindex)
	{
		free(parentarray[j]);
		j++;
	}
	free(parentarray);
	return (NULL);
}

void	cleanup(t_shell_data *shell)
{
	redirect_to_terminal();
	free_var_pipe_list(shell->pipe_list);
	shell->pipe_list = NULL;
	shell->pipes_count = 0;
	shell->heredoc_launched = false;
	shell->pipe_list = NULL;
}

void	handle_exit(t_shell_data *shell, char *input)
{
	if (input == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		cleanup(shell);
		exit(shell->last_exit_code);
	}
}

void	clear_shell_data(t_shell_data *shell)
{
	if (shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (shell->variables)
	{
		free_env_list(shell->variables);
		shell->variables = NULL;
	}
	free_var_pipe_list(shell->pipe_list);
	free_string_array(shell->exec_env);
	restore_control_echo();
	free(shell);
}
