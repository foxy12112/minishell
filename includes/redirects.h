/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:36:43 by macbook           #+#    #+#             */
/*   Updated: 2025/01/17 17:25:06 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H
# include "minishell.h"

// redirects
int		redirect_output(t_shell_data *shell, char *filename);
void	redirect_input(t_shell_data *shell, const char *filename);
int		redirect_output_append(t_shell_data *shell, const char *filename);
// heredoc
char	*expand_heredoc_line(t_shell_data *shell, char *line);
int		redirect_heredoc_launch(t_shell_data *shell, char *file);
int		redirect_to_terminal(void);
void	remove_char(char *str, char c);
char	*generate_heredoc_file(void);
void	custom_handler(int signal);

#endif