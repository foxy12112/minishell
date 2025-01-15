/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:01:47 by ldick             #+#    #+#             */
/*   Updated: 2024/03/20 10:29:36 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_nbr(int n, int *milk)
{
	if (n == -2147483648)
	{
		ft_print_str("-2147483648", milk);
		return ;
	}
	else if (n < 0)
	{
		ft_print_char('-', milk);
		n = -n;
	}
	if (n >= 10)
	{
		ft_print_nbr((n / 10), milk);
	}
	ft_print_char(n % 10 + '0', milk);
}
