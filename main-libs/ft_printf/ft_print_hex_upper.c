/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_upper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:53:57 by ldick             #+#    #+#             */
/*   Updated: 2024/03/19 11:35:13 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_hex_upper(unsigned int n, int *milk)
{
	if (n >= 16)
	{
		ft_print_hex_upper((n / 16), milk);
		ft_print_hex_upper((n % 16), milk);
	}
	else if (n < 10)
		ft_print_char((n + '0'), milk);
	else
		ft_print_char((n + 55), milk);
}
