/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:54:47 by macbook           #+#    #+#             */
/*   Updated: 2024/12/15 14:54:24 by auplisas         ###   ########.fr       */
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
	fflush(stdout);
	if (execvp(file, argv) == -1)
	{
		perror("Ececvp failed");
		exit(EXIT_FAILURE);
	}
}

char	**remove_quotes_from_array(char **array)
{
	int		i;
	int		j;
	int		size;
	char	**new_array;

	j = 0;
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
		{
			new_array[i] = remove_quotes(array[i]);
		}
		else
			new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
		{
			j = 0;
			while (j < i)
			{
				free(new_array[j]);
				j++;
			}
			free(new_array);
			return (NULL);
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	cell_launch(char **args)
{
	char **parsed_args;
	pid_t pid = ft_fork();
	parsed_args = remove_quotes_from_array(args);
	// print_arofars(parsed_args);
	if (pid == 0)
	{
		ft_execvp(parsed_args[0], parsed_args);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}
	free_char_string(parsed_args);
}