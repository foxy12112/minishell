/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:39:37 by ldick             #+#    #+#             */
/*   Updated: 2024/03/19 11:35:14 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex_lower(unsigned int n, int *milk)
{
	if (n >= 16)
	{
		ft_print_hex_lower((n / 16), milk);
		ft_print_hex_lower((n % 16), milk);
	}
	else if (n < 10)
		ft_print_char((n + '0'), milk);
	else
		ft_print_char((n + 87), milk);
}
