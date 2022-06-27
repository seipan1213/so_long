/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:52:09 by sehattor          #+#    #+#             */
/*   Updated: 2022/06/27 21:57:19 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map(t_so_long *sl)
{
	check_map_char(sl);
	is_close_map(sl);
}

void	check_map_char(t_so_long *sl)
{
	int	x;
	int	y;
	int	pl;
	int	goal;
	int	item;

	pl = 0;
	goal = 0;
	item = 0;
	y = -1;
	while (++y < sl->gm.height)
	{
		x = -1;
		while (++x < sl->gm.width)
		{
			if (sl->gm.map[y][x] == PL)
				pl++;
			else if (sl->gm.map[y][x] == GOAL)
				goal++;
			else if (sl->gm.map[y][x] == ITEM)
				item++;
		}
	}
	if (goal != 1 || pl != 1 || item <= 0)
		put_exit_err(ERR_MAP_MISSING);
}

void	bfs_utils(t_so_long *sl, int **map, t_list **lst, int *item_g_sum)
{
	const int	dx[4] = {0, 1, 0, -1};
	const int	dy[4] = {1, 0, -1, 0};
	t_ipair		p;
	int			c;

	p = *(t_ipair *)(*lst)->content;
	if (sl->gm.map[p.first][p.second] == ITEM
		|| sl->gm.map[p.first][p.second] == GOAL)
		(*item_g_sum)++;
	ft_lstdel_front(lst);
	c = -1;
	if (is_edge(sl, p))
		put_exit_err(ERR_MAP_NOT_ENCLOSED);
	while (++c < 4)
	{
		if (sl->gm.map[p.first + dx[c]][p.second + dy[c]] != WALL
			&& sl->gm.map[p.first + dx[c]][p.second + dy[c]] != GOAL
			&& map[p.first + dx[c]][p.second + dy[c]] == 0)
		{
			ft_lstadd_back(lst,
				ft_lstnew(make_ipair(p.first + dx[c], p.second + dy[c])));
			map[p.first + dx[c]][p.second + dy[c]] = 1;
		}
	}
}

void	map_bfs(t_so_long *sl, int **map, t_ipair p)
{
	t_list	**lst;
	int		item_g_sum;

	lst = (t_list **)ft_calloc(1, sizeof(t_list *));
	*lst = ft_lstnew(make_ipair(p.first, p.second));
	item_g_sum = 0;
	while (*lst)
		bfs_utils(sl, map, lst, &item_g_sum);
	bfs_clear(lst);
	if (item_g_sum != sl->gm.item_sum + 1)
		put_exit_err(ERR_MAP_CANT_FINISH);
}

void	is_close_map(t_so_long *sl)
{
	int		**map;
	int		i;
	t_ipair	p;

	i = 0;
	map = (int **)malloc(sizeof(int *) * sl->gm.height);
	if (!map)
		put_exit_err(ERR_MALLOC);
	while (i < sl->gm.height)
	{
		map[i] = (int *)ft_calloc(sl->gm.width, sizeof(int));
		if (!map[i])
			put_exit_err(ERR_MALLOC);
		i++;
	}
	p.first = sl->gm.pl.y;
	p.second = sl->gm.pl.x;
	map_bfs(sl, map, p);
	while (i-- > 0)
		free(map[i]);
	free(map);
}
