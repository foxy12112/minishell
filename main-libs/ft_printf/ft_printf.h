/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:57:00 by ldick             #+#    #+#             */
/*   Updated: 2024/06/09 15:45:27 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

void	ft_print_char(int c, int *milk);
void	ft_print_hex_lower(unsigned int n, int *milk);
void	ft_print_nbr(int n, int *milk);
void	ft_print_pointers(void *p, int *milk);
void	ft_print_str(char *s, int *milk);
void	ft_print_uns_d(unsigned int n, int *milk);
void	ft_print_hex_upper(unsigned int n, int *milk);
/**
 * @brief personal implementation of the function printf
 * @param[in] format - the function on which to use after a %
 * @note the functions available are
 * @note %, which prints a %;
 * @note c which prints a single character;
 * @note s which prints a string of characters;
 * @note p which prints a pointer address;
 * @note d or i which prints a integer;
 * @note u which prints an unsigned int
 * @note x which prints a lowercase hexadecimal int
 * @note X which prints a uppercase hexadecimal int
 * @return returns a string with format applied to every defined character
*/
int		ft_printf(const char *format, ...);

#endif