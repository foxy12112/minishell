/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:54:47 by macbook           #+#    #+#             */
/*   Updated: 2024/12/17 09:13:19 by ldick            ###   ########.fr       */
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

void	ft_execvp(const char *file, char *const argv[])
{
	if (!file || !argv)
	{
		printf("Execvp: invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	if (execvp(file, argv) == -1)
	{
		printf("Ececvp failed\n");
		exit(EXIT_FAILURE);
	}
}

char	**remove_quotes_from_array(char **array)
{
	int		i;
	int		size;
	char	**new_array;

	i = 0;
	size = 0;
	while (array[size] != NULL)
		size++;
	new_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_array)
		return (NULL);
	while (array[i] != NULL)
	{
		if (string_in_doublequotes(array[i])
			|| string_in_singlequotes(array[i]))
			new_array[i] = remove_quotes(array[i]);
		else
			new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
			return (free_all(new_array, i), NULL);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	cell_launch(char **args)
{
	char	**parsed_args;
	pid_t	pid;
	int		status;

	pid = ft_fork();
	parsed_args = remove_quotes_from_array(args);
	if (pid == 0)
	{
		ft_execvp(parsed_args[0], parsed_args);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	free_string_array(parsed_args);
}
