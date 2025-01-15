/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:09:01 by ldick             #+#    #+#             */
/*   Updated: 2024/06/15 10:40:04 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_check_format(va_list ap, const char *format, int *milk,
		size_t *i)
{
	if (format[*i] == '%')
		ft_print_char(format[*i], milk);
	else if (format[*i] == 'c')
		ft_print_char(va_arg(ap, int), milk);
	else if (format[*i] == 's')
		ft_print_str(va_arg(ap, char *), milk);
	else if (format[*i] == 'p')
		ft_print_pointers(va_arg(ap, void *), milk);
	else if (format[*i] == 'd' || format[*i] == 'i')
		ft_print_nbr(va_arg(ap, int), milk);
	else if (format[*i] == 'u')
		ft_print_uns_d(va_arg(ap, unsigned int), milk);
	else if (format[*i] == 'x')
		ft_print_hex_lower(va_arg(ap, unsigned long), milk);
	else if (format[*i] == 'X')
		ft_print_hex_upper(va_arg(ap, unsigned long), milk);
	(*i)++;
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		milk;
	size_t	n;

	va_start(ap, format);
	i = 0;
	milk = 0;
	n = ft_strlen(format);
	if (format == NULL)
		return (0);
	while (format[i] && (i < n))
	{
		if (format[i] != '%')
			ft_print_char(format[i++], &milk);
		else
		{
			i++;
			ft_check_format(ap, format, &milk, &i);
		}
	}
	va_end(ap);
	return (milk);
}
