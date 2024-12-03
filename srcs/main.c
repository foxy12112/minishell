/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:18 by macbook           #+#    #+#             */
/*   Updated: 2024/12/03 02:32:45 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_arguments(char *args_ar)
{
	int	i;

	i = 0;
	while (args_ar[i])
	{
		printf("%s\n", args_ar[i]);
		i++;
	}
	return (0);
}

int	main(void)
{
	char **newstr;

	newstr = ft_split("Helo, my friend", ' ');
	execute_arguments(newstr);
	return (0);
}