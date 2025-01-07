/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:36:43 by macbook           #+#    #+#             */
/*   Updated: 2025/01/07 05:12:34 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirects
int		redirect_output(t_shell_data *shell, const char *filename);
void	redirect_input(t_shell_data *shell, const char *filename);
int		redirect_output_append(t_shell_data *shell, const char *filename);
void	redirect_input_heredoc(t_shell_data *shell, const char *delimiter);
int		redirect_to_terminal(t_shell_data *shell);