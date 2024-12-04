/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:36:55 by ldick             #+#    #+#             */
/*   Updated: 2024/12/04 16:35:40 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../main-libs/libs.h"
# include <fcntl.h>
# include <limits.h>
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
int						fd_cd(char *path);
int						ft_pwd(void);
#endif