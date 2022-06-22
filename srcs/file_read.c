#include "so_long.h"

void read_img(t_so_long *sl, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(sl->mlx, path, &img->width, &img->height);
	if (!img->img)
		put_exit_err(ERR_MALLOC);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
								  &img->llen, &img->endian);
}

t_dc_lst *read_map(char *file_path)
{
	int fd;
	char *line;
	int ret;
	t_dc_lst *map;
	int width;

	fd = open(file_path, O_RDONLY);
	if (fd <= 0)
		put_exit_err(ERR_FILE);
	map = dc_lst_init();
	ret = get_next_line(fd, &line);
	dc_lst_addback(map, line);
	width = ft_strlen(line);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret <= 0)
			break;
		dc_lst_addback(map, line);
		if (width != (int)ft_strlen(line))
			put_exit_err(ERR_FILE);
	}
	free(line);
	return (map);
}
