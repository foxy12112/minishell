/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:54:47 by macbook           #+#    #+#             */
/*   Updated: 2025/01/17 21:25:34 by macbook          ###   ########.fr       */
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

char	*find_path(t_env_list *env)
{
	char	*path;

	path = NULL;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			path = ft_strdup(env->value);
		}
		env = env->next;
	}
	return (path);
}

char	*find_cmd(t_env_list *env, char *cmd)
{
	char	*cmd_new;
	char	*tmp;
	char	*ret;
	char	*path;
	char	**splitted_path;

	path = find_path(env);
	if(!path)
		return (NULL);
	printf("CRAZY FROG\n");
	// splitted_path=ft_split(path, ':');
	// print_arofars(splitted_path);
	(void)cmd_new;
	(void)tmp;
	(void)ret;
	(void)path;
	(void)cmd;
	(void)splitted_path;
	// while (*splitted_path)
	// {
	// 	tmp = ft_strjoin(*splitted_path, "/");
	// 	ret = ft_strjoin(tmp, cmd);
	// 	free(tmp);
	// 	tmp = NULL;
	// 	if (access(ret, 0) == 0)
	// 	{
	// 		return (ret);
	// 	}
	// 	free(ret);
	// 	splitted_path++;
	// }
	// free(path);
	// if (access(cmd, 0) == 0)
	// {
	// 	cmd_new = ft_strdup(cmd);
	// 	return (cmd_new);
	// }
	// else
	// {
	// 	printf("GELA TROLISHVILI\n");
	// }
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
	command = find_cmd(shell->env, parsed_args[0]);
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