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

void draw_img(t_so_long *sl, t_img *img, t_ipair p, bool is_ignore)
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
			if (!is_ignore || color != ignore_color)
				my_mlx_pixel_put(&sl->win_img, x + p.first, y + p.second, color);
			x++;
		}
		y++;
	}
}

void draw_select_img(t_so_long *sl, int map_x, int map_y)
{
	int key;
	t_ipair p;

	key = sl->gm.map[map_y][map_x];
	p.first = map_x * sl->gm.s_width;
	p.second = map_y * sl->gm.s_height;
	draw_img(sl, &sl->back_img, p, false);
	if (key == WALL)
		draw_img(sl, &sl->wall_img, p, true);
	else if (key == ITEM)
		draw_img(sl, &sl->item_img, p, true);
	else if (key == GOAL)
		draw_img(sl, &sl->goal_img, p, true);
	else if (key == PL)
		draw_img(sl, &sl->player_img, p, true);
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