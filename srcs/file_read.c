/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:10:52 by sehattor          #+#    #+#             */
/*   Updated: 2022/06/25 20:42:23 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_img(t_so_long *sl, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(sl->mlx, path, &img->width, &img->height);
	if (!img->img)
		put_exit_err(ERR_MLX);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->llen, &img->endian);
}

t_dc_lst	*read_map(char *file_path)
{
	int			fd;
	char		*line;
	int			ret;
	t_dc_lst	*map;
	int			width;

	fd = open(file_path, O_RDONLY);
	if (fd <= 0)
		put_exit_err(ERR_FILE);
	map = dc_lst_init();
	ret = 1;
	width = -1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret <= 0 && !ft_strncmp(line, "\0", 1))
			break ;
		dc_lst_addback(map, line);
		if (width == -1)
			width = ft_strlen(line);
		if (width != (int)ft_strlen(line))
			put_exit_err(ERR_MAP_NOT_RECT);
	}
	free(line);
	return (map);
}
