/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2024/12/05 19:27:11 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenize(char *input)
{
	//slpit into small parts, send back to sasha
}

void	display(void)
{
	char	*input;

	while (1)
	{
		input = readline("waiting for input:");
		add_history(input);
		if (!ft_strncmp(input, "exit", 5))
			break ;
		//take input, tokenize it,
		ft_tokenize(input)
	}
}
