/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:36:55 by ldick             #+#    #+#             */
/*   Updated: 2024/12/03 22:14:36 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../main-libs/main-libs.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// > - RDR_COMMAND_TO_INPUT, < - RDR_INPUT_TO_COMMAND, << -
typedef enum s_operation_type
{
	RDR_INPUT,
	RDR_OUTPUT,
	RDR_HEREDOC,
	RDR_APPEND,
	PIPE,
	NO_RDR,
}						t_operation_type;

typedef struct s_shell_data
{
	t_operation_type	operation_type;
}						t_shell_data;

typedef struct s_nodes
{
}						t_nodes;

int						main(int argc, char **argv);
int						utils(void);

// builtins
int						ft_echo(char **args, int fd);

#endif