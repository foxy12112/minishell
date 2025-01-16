/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:50:31 by ldick             #+#    #+#             */
/*   Updated: 2024/03/19 13:40:35 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_uns_d(unsigned int n, int *milk)
{
	if (n < 0)
		write(1, "(null)", 6);
	if (n < 10)
		ft_print_char((n + '0'), milk);
	else
	{
		ft_print_nbr((n / 10), milk);
		ft_print_nbr((n % 10), milk);
	}
}
