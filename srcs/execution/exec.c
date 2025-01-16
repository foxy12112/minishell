/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:54:47 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 21:05:28 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("Fork Failed");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

char	**true_quote_removal_from_array(char **array)
{
	int		i;
	int		size;
	char	**new_array;

	i = 0;
	size = 0;
	while (array[size])
		size++;
	new_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_array)
		return (NULL);
	while (array[i] != NULL)
	{
		if (string_in_doublequotes(array[i])
			|| string_in_singlequotes(array[i]))
			new_array[i] = ft_strdup(true_quote_removal(array[i]));
		else
			new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
			return (free_all(new_array, i), NULL);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

char	*find_cmd(char **path, char *cmd)
{
	char	*cmd_new;
	char	*tmp;
	char	*ret;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (access(ret, 0) == 0)
		{
			return (ret);
		}
		free(ret);
		path++;
	}
	if (access(cmd, 0) == 0)
	{
		cmd_new = ft_strdup(cmd);
		return (cmd_new);
	}
	return (NULL);
}

// echo $"42"$
// echo "this is $HOME and we will"

int	cell_launch(t_shell_data *shell, char **args)
{
	char	**parsed_args;
	pid_t	pid;
	int		status;
	char	*command;

	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("Failed to fork\n", STDERR_FILENO), 1);
	status = 0;
	parsed_args = true_quote_removal_from_array(args);
	if (!parsed_args)
		return (127);
	command = find_cmd(shell->exec_env, parsed_args[0]);
	shell->last_exit_code = EXIT_SUCCESS;
	if (!command)
		return (free_string_array(parsed_args), 127);
	if (pid == 0)
		execve(command, parsed_args, shell->enviroment);
	waitpid(pid, &status, WUNTRACED);
	free(command);
	free_string_array(parsed_args);
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	return (shell->last_exit_code);
}

// else if (WIFSIGNALED(status))
// 	shell->last_exit_code = 128 + WTERMSIG(status);