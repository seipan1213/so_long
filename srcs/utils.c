/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:59:43 by sehattor          #+#    #+#             */
/*   Updated: 2022/06/25 19:59:52 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_exit_err(int type)
{
	if (type == ERR_MALLOC)
		ft_putendl_fd(MALLOC_ERROR, STDERR_FILENO);
	else if (type == ERR_MLX)
		ft_putendl_fd(MLX_ERROR, STDERR_FILENO);
	else if (type == ERR_ARG)
		ft_putendl_fd(ARG_ERR, STDERR_FILENO);
	else if (type == ERR_FILE)
		ft_putendl_fd(FILE_ERR, STDERR_FILENO);
	else if (type == ERR_MAP_MISSING)
		ft_putendl_fd(MAP_MISSING_ERR, STDERR_FILENO);
	else if (type == ERR_MAP_NOT_ENCLOSED)
		ft_putendl_fd(MAP_NOT_ENCLOSED_ERR, STDERR_FILENO);
	else if (type == ERR_MAP_NOT_RECT)
		ft_putendl_fd(MAP_NOT_RECT_ERR, STDERR_FILENO);
	else if (type == ERR_MAP_UN_KNOW_CHAR)
		ft_putendl_fd(MAP_UN_KNOW_CHAR_ERR, STDERR_FILENO);
	else if (type == ERR_MAP_CANT_FINISH)
		ft_putendl_fd(MAP_CANT_FINISH_ERR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

t_ipair	*make_ipair(int i, int j)
{
	t_ipair	*p;

	p = (t_ipair *)malloc(sizeof(t_ipair));
	p->first = i;
	p->second = j;
	return (p);
}
