/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:36:43 by macbook           #+#    #+#             */
/*   Updated: 2025/01/10 11:11:07 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirects
int		redirect_output(t_shell_data *shell, const char *filename);
void	redirect_input(t_shell_data *shell, const char *filename);
int		redirect_output_append(t_shell_data *shell, const char *filename);
void	redirect_input_heredoc(t_shell_data *shell, char *delimiter);
int		redirect_to_terminal(void);