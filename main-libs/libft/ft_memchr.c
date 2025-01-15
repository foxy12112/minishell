/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:03:58 by ldick             #+#    #+#             */
/*   Updated: 2024/03/09 09:32:21 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*sb;

	i = 0;
	sb = (char *)s;
	while (i < n)
	{
		if (sb[i] == (char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
