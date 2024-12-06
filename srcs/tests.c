/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:18:43 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/06 03:50:03 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	test_cd(t_shell_data *shell)
{
	printf("Printing OLD PWDs:\n\n");
	printf("PWD: %s\n", retrieve_variable(shell, "PWD"));
	printf("OLDPWD: %s\n", retrieve_variable(shell, "OLDPWD"));
	fd_cd(shell, "../");
	printf("\nPrinting Renewed PWDs:\n\n");
	printf("PWD: %s\n", retrieve_variable(shell, "PWD"));
	printf("OLDPWD: %s\n", retrieve_variable(shell, "OLDPWD"));
}

void	test_export(t_shell_data *shell)
{
	printf("Printing Default Variable List:\n\n");
	print_variables_list(shell->variables);
	ft_export(shell, ft_split("HI=MTE YELLO=YUUU", ' '));
	printf("\nPrinting Renewed Variable List:\n\n");
	print_variables_list(shell->variables);
}

void	test_echo(void)
{
	ft_echo(ft_split("HELO WORLD THIS IS ME", ' '), 1, false);
}

void	test_env(t_shell_data *shell)
{
	ft_env(shell);
}

void	test_pwd(void)
{
	ft_pwd();
}

void	test_unset(t_shell_data *shell)
{
	ft_export(shell, ft_split("HI=MTE YELLO=YUUU", ' '));
	printf("\nPrinting Default ENV List:\n\n");
	print_env_list(shell->env);
	ft_unset(shell, "HI");
	printf("\nPrinting New ENV List:\n\n");
	print_env_list(shell->env);
}
