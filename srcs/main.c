/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:18 by macbook           #+#    #+#             */
/*   Updated: 2024/12/05 05:18:46 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	select_operation_type(char **args_ar, t_shell_data *data_tree)
{
	int	i;

	i = 0;
	while (args_ar[i])
	{
		if (ft_strcmp(args_ar[i], "<") == 0)
			data_tree->operation_type = RDR_OUTPUT;
		else if (ft_strcmp(args_ar[i], ">") == 0)
			data_tree->operation_type = RDR_INPUT;
		else if (ft_strcmp(args_ar[i], ">>") == 0)
			data_tree->operation_type = RDR_APPEND;
		else if (ft_strcmp(args_ar[i], "<<") == 0)
			data_tree->operation_type = RDR_HEREDOC;
		else if (ft_strcmp(args_ar[i], "|") == 0)
			data_tree->operation_type = PIPE;
		else
			data_tree->operation_type = NO_RDR;
	}
}

int	execute_arguments(char **args_ar)
{
	t_shell_data	*data_tree;

	data_tree = malloc(1 * sizeof(t_shell_data));
	if (!data_tree)
		return (1);
	select_operation_type(args_ar, data_tree);
	if (data_tree->operation_type != NO_RDR)
	{
		// launch_redirect();
	}
	return (0);
}

void swap_nodes(t_env_list *a, t_env_list *b) {
    char *temp_key = a->key;
    char *temp_value = a->value;

    a->key = b->key;
    a->value = b->value;

    b->key = temp_key;
    b->value = temp_value;
}

// Bubble sort to sort the list by keys alphabetically
void sort_env_list(t_env_list *head) {
    int swapped;
    t_env_list *ptr1;
    t_env_list *ptr2 = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        // Traverse the list and compare adjacent nodes
        while (ptr1->next != ptr2) {
            if (strcmp(ptr1->key, ptr1->next->key) > 0) {
                swap_nodes(ptr1, ptr1->next); // Swap keys and values
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        ptr2 = ptr1;  // Set the last sorted node to prevent checking it again
    } while (swapped);  // Continue until no more swaps are needed
}

int	initialize_shell(t_shell_data *shell)
{
	shell->env = initialize_env();
	shell->operation_type = NO_RDR;
	return (0);
}


void	leaks(void)
{
	system("leaks minishella");
}

int	main(int argc, char **argv)
{
	t_shell_data	*shell;

	atexit(leaks);
	(void)argv;
	(void)argc;
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	print_env_list(shell->variables);
	free_env_list(shell->variables);
	free(shell);
	return (0);
}

// char **newstr;
// execute_arguments(newstr);

// fd_cd("../");
// ft_echo(ft_split("HELO WORLD THIS IS ME", ' '), 1);
// ft_pwd();

// newstr = ft_split("VAR1=TES1 VAR2=TES2 VAR3=TES3", ' ');
// ft_export(shell, newstr);