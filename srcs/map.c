/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:49:18 by sehattor          #+#    #+#             */
/*   Updated: 2022/06/25 19:49:47 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_type(t_so_long *sl, int type, int x, int y)
{
	if (type == PL)
	{
		sl->gm.pl.x = x;
		sl->gm.pl.y = y;
	}
	else if (type == ITEM)
		sl->gm.item_sum++;
}

void	conv_map(t_so_long *sl, t_dc_lst *map)
{
	int	y;
	int	x;
	int	type;

	sl->gm.map = malloc(sizeof(int *) * sl->gm.height);
	if (sl->gm.map == NULL)
		put_exit_err(ERR_MALLOC);
	map = get_first_lst(map);
	y = -1;
	while (++y < sl->gm.height)
	{
		sl->gm.map[y] = malloc(sizeof(int) * sl->gm.width);
		if (sl->gm.map[y] == NULL)
			put_exit_err(ERR_MALLOC);
		x = -1;
		while (++x < sl->gm.width)
		{
			type = map_type(map->value[x]);
			if (type == -1)
				put_exit_err(ERR_MAP_UN_KNOW_CHAR);
			set_type(sl, type, x, y);
			sl->gm.map[y][x] = map_type(map->value[x]);
		}
		map = map->next;
	}
}

int	map_type(char c)
{
	if (c == '0')
		return (SP);
	else if (c == '1')
		return (WALL);
	else if (c == 'E')
		return (GOAL);
	else if (c == 'C')
		return (ITEM);
	else if (c == 'P')
		return (PL);
	return (-1);
}
