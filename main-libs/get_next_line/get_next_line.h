/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:15:28 by ldick             #+#    #+#             */
/*   Updated: 2024/04/29 12:58:31 by ldick            ###   ########.fr       */
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

/**
 * @brief reads from a a file
 * reads a text until a new line is encountered
 * @note reads one line at a time, using a while loop you can read throuh a text file line by line
 * 
 * @param[in] fd - the file descriptor from which to read from
 * @return read line
*/
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