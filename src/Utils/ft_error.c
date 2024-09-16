/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgmelin <tgmelin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:49:45 by tgmelin           #+#    #+#             */
/*   Updated: 2024/09/16 19:25:39 by tgmelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_ft_err_data *_data, const char *_msg, int _rtrn)
{
	static void	*allocated_data;
	static void	(*err_function)(void *_allocated_data);

	if (_data)
	{
		allocated_data = _data->alloc_data;
		err_function = _data->teardown_func;
		return ;
	}
	write(2, _msg, ft_strlen(_msg));
	err_function(allocated_data);
	exit(1);
}
