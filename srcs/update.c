#include "so_long.h"

int update(t_so_long *sl)
{
	game_update(sl);
	mlx_put_image_to_window(sl->mlx, sl->win, sl->win_img.img, 0, 0);
	return (0);
}

void game_update(t_so_long *sl)
{
	draw_back(sl);
	draw_imgs(sl);
}