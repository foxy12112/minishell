/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:19:50 by ldick             #+#    #+#             */
/*   Updated: 2024/03/20 11:05:59 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_gimme_hex(unsigned long nbr, int *milk)
{
	if (nbr >= 16)
	{
		ft_gimme_hex((nbr / 16), milk);
		ft_gimme_hex((nbr % 16), milk);
	}
	else if (nbr < 10)
		ft_print_char((nbr + '0'), milk);
	else
		ft_print_char((nbr + 87), milk);
}

void	ft_print_pointers(void *p, int *milk)
{
	ft_print_str("0x", milk);
	ft_gimme_hex((unsigned long)p, milk);
}
