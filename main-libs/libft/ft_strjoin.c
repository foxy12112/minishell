/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:19:23 by ldick             #+#    #+#             */
/*   Updated: 2024/03/10 14:28:33 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	total_len;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	output = (char *)malloc (total_len + 1);
	if (!output)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	ft_memcpy(output, s1, ft_strlen(s1));
	ft_memcpy(output + ft_strlen(s1), s2, ft_strlen(s2));
	output[total_len] = '\0';
	return (output);
}
