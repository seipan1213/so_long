/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:20:48 by sehattor          #+#    #+#             */
/*   Updated: 2022/06/25 20:21:15 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	bfs_clear(t_list **lst)
{
	ft_lstclear(lst, &free);
	free(lst);
}

bool	is_edge(t_so_long *sl, t_ipair p)
{
	return (p.first <= 0 || p.second <= 0
		|| p.first >= sl->gm.height - 1 || p.second >= sl->gm.width - 1);
}
