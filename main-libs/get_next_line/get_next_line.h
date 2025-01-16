/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:15:28 by ldick             #+#    #+#             */
/*   Updated: 2025/01/16 21:30:45 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
size_t	gnl_strlen(char *s);
char	*read_bytes(int fd, char *full_read);
char	*ft_get_line(char *full_read);
char	*update_rest(char *full_read);
char	*ft_new_str(char *s1);
size_t	gnl_strlcpy(char *dest, const char *src, size_t len);

#endif