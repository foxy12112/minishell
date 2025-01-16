/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:22:56 by ldick             #+#    #+#             */
/*   Updated: 2024/03/08 17:32:04 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int			i;
	char		*srcc;
	char		*dstt;

	i = 0;
	srcc = (char *)src;
	dstt = dst;
	if (dst == src || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	while (n--)
	{
		dstt[i] = srcc[i];
		i++;
	}
	return (dst);
}
