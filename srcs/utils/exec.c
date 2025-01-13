/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:54:47 by macbook           #+#    #+#             */
/*   Updated: 2025/01/13 02:23:39 by auplisas         ###   ########.fr       */
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
			new_array[i] = true_quote_removal(array[i]);
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
	char	*tmp;
	char	*ret;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(ret, 0) == 0)
			return (ret);
		free(ret);
		path++;
	}
	if (access(cmd, 0) == 0)
		return (cmd);
	return (NULL);
}

int	cell_launch(t_shell_data *shell, char **args)
{
	char **parsed_args;
	pid_t pid;
	int status;
	char *command;

	pid = fork();
	if (pid < 0)
	{
		printf("failed\n");
		return (1);
	}
	status = 0;
	parsed_args = true_quote_removal_from_array(args);
	command = find_cmd(shell->exec_env, parsed_args[0]);
	if (!command)
	{
		// printf("\ncommand not found: %s\n", parsed_args[0]);
		free_string_array(parsed_args);
		free_string_array(args);
		return (127);
	}
	// printf("%s\n", command);
	// print_two_d(parsed_args);
	if (pid == 0)
	{
		// printf("%s\n", command);
		if (execve(command, parsed_args, shell->enviroment) == -1)
		{
			free(command);
			free_string_array(parsed_args);
			free_string_array(args);
			shell->last_exit_code = 69;
			return (69);
		}
	}
	waitpid(pid, &status, WUNTRACED);
	// wait_for_process(pid);
	// waitpid(pidm )
	free_string_array(args);
	free_string_array(parsed_args);
	// free(command);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}