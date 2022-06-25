/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:59:29 by sehattor          #+#    #+#             */
/*   Updated: 2022/06/25 19:59:35 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clear_lst(t_dc_lst *lst)
{
	int	lst_size;
	int	index;

	lst_size = get_lst_size(lst) + 1;
	index = 0;
	while (index < lst_size)
	{
		delete_lst(lst->next);
		index++;
	}
}

void	delete_lst(t_dc_lst *lst)
{
	t_dc_lst	*prev;
	t_dc_lst	*next;

	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
	free(lst->value);
	free(lst);
}
