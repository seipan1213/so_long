#include "so_long.h"

void draw_back(t_so_long *sl)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&sl->win_img, x, y, sl->gm.back_color);
			x++;
		}
		y++;
	}
}

void draw_img(t_so_long *sl, t_img *img, int s_x, int s_y)
{
	int y;
	int x;
	size_t color;
	size_t ignore_color;

	y = 0;
	ignore_color = pic_color(*img, 0, 0);
	while (y < sl->gm.s_height)
	{
		x = 0;
		while (x < sl->gm.s_width)
		{
			color = pic_color(*img, x * (img->width / (double)sl->gm.s_width), y * (img->height / (double)sl->gm.s_height));
			if (color != ignore_color)
				my_mlx_pixel_put(&sl->win_img, x + s_x, y + s_y, color);
			x++;
		}
		y++;
	}
}

void draw_select_img(t_so_long *sl, int map_x, int map_y)
{
	int key;

	key = sl->gm.map[map_y][map_x];
	if (key == WALL)
		draw_img(sl, &sl->wall_img, map_x * sl->gm.s_width, map_y * sl->gm.s_height);
	else if (key == ITEM)
		draw_img(sl, &sl->item_img, map_x * sl->gm.s_width, map_y * sl->gm.s_height);
	else if (key == GOAL)
		draw_img(sl, &sl->goal_img, map_x * sl->gm.s_width, map_y * sl->gm.s_height);
	else if (key == PL)
		draw_img(sl, &sl->player_img, map_x * sl->gm.s_width, map_y * sl->gm.s_height);
}

void draw_imgs(t_so_long *sl)
{
	int map_x;
	int map_y;

	map_y = 0;
	while (map_y < sl->gm.height)
	{
		map_x = 0;
		while (map_x < sl->gm.width)
		{
			draw_select_img(sl, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}