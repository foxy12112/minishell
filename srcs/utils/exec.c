/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:54:47 by macbook           #+#    #+#             */
/*   Updated: 2024/12/15 12:57:21 by auplisas         ###   ########.fr       */
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

char **remove_quotes_from_array(char **array)
{
    int i;
    int size;
    char **new_array;

    i = 0;
    size = 0;

    // Calculate the size of the input array (number of strings)
    while (array[size] != NULL)
        size++;

    // Allocate memory for the new array (same size as the input array)
    new_array = (char **)malloc(sizeof(char *) * (size + 1));  // +1 for the NULL terminator
    if (!new_array)
        return NULL;

    // Remove quotes from each string in the array
    while (array[i] != NULL)
    {
		if(string_in_doublequotes(array[i]) || string_in_singlequotes(array[i]))
		{
		 	new_array[i] = remove_quotes(array[i]);	
		}else
		{
			new_array[i] = ft_strdup(array[i]);
		}
		// new_array[i] = remove_quotes(array[i]);
        if (!new_array[i])  // If allocation for any string fails
        {
            // Free all previously allocated memory
            int j = 0;
            while (j < i)
            {
                free(new_array[j]);
                j++;
            }
            free(new_array);
            return NULL;
        }
        i++;
    }

    new_array[i] = NULL;  // Null-terminate the new array of strings

    return new_array;
}

void	cell_launch(char **args)
{
	char **parsed_args;
	pid_t pid = ft_fork();
	parsed_args=remove_quotes_from_array(args);
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