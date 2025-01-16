/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordconut.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 07:56:04 by ldick             #+#    #+#             */
/*   Updated: 2024/05/24 08:05:34 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wordcount(char *str, int delimiter)
{
	int	count;
	int	in_word;

	if (!str)
		return (0);
	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == delimiter)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}
