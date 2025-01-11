/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:36:43 by macbook           #+#    #+#             */
/*   Updated: 2025/01/11 05:20:02 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirects
int		redirect_output(t_shell_data *shell, const char *filename);
void	redirect_input(t_shell_data *shell, const char *filename);
int		redirect_output_append(t_shell_data *shell, const char *filename);
void	redirect_input_heredoc(t_shell_data *shell, const char *delimiter);
void restore_stdin(t_shell_data *shell);
int		redirect_to_terminal(void);