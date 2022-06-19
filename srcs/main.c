#include "so_long.h"

int close_btn_hook(int keycode, t_so_long *sl)
{
	(void)sl;
	(void)keycode;
	exit(EXIT_FAILURE);
}

void sl_init(t_so_long *sl)
{
	view_init(sl);
	imgs_init(sl);
	game_init(sl);
}

void game_init(t_so_long *sl) // TODO: MAP作成処理
{
	sl->gm.width = 4;
	sl->gm.height = 5;
	sl->gm.item_sum = 0;
	sl->gm.s_width = WIDTH / sl->gm.width;
	sl->gm.s_height = HEIGHT / sl->gm.height;
	sl->gm.back_color = create_trgb(0, 24, 235, 249); // TODO: 定数
	return;
}

void view_init(t_so_long *sl)
{
	sl->mlx = mlx_init();
	if (!sl->mlx)
		put_exit_err(ERR_MLX);
	sl->win = mlx_new_window(sl->mlx, WIDTH, HEIGHT, TITLE);
	if (!sl->win)
		put_exit_err(ERR_MLX);
	sl->win_img.img = mlx_new_image(sl->mlx, WIDTH, HEIGHT);
	if (!sl->win_img.img)
		put_exit_err(ERR_MLX);
	sl->win_img.addr = mlx_get_data_addr(sl->win_img.img, &sl->win_img.bpp,
										 &sl->win_img.llen, &sl->win_img.endian);
	mlx_do_key_autorepeatoff(sl->mlx);
}

void imgs_init(t_so_long *sl)
{
	read_img(sl, &sl->player_img, PLAYER_PATH);
	read_img(sl, &sl->goal_img, GOAL_PATH);
	read_img(sl, &sl->start_img, START_PATH);
	read_img(sl, &sl->wall_img, WALL_PATH);
	read_img(sl, &sl->item_img, ITEM_PATH);
}

void read_img(t_so_long *sl, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(sl->mlx, path, &img->width, &img->height);
	if (!img->img)
		put_exit_err(ERR_MALLOC);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
								  &img->llen, &img->endian);
}

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
	char key;

	key = g_map[map_y][map_x];
	if (key == '1')
		draw_img(sl, &sl->wall_img, map_x * sl->gm.s_width, map_y * sl->gm.s_height);
	else if (key == 'C')
		draw_img(sl, &sl->item_img, map_x * sl->gm.s_width, map_y * sl->gm.s_height);
	else if (key == 'E')
		draw_img(sl, &sl->goal_img, map_x * sl->gm.s_width, map_y * sl->gm.s_height);
	else if (key == 'P')
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

void game_update(t_so_long *sl)
{
	draw_back(sl);
	draw_imgs(sl);
}

int main_loop(t_so_long *sl)
{
	(void)sl;
	game_update(sl);
	mlx_put_image_to_window(sl->mlx, sl->win, sl->win_img.img, 0, 0);
	return (0);
}

int key_press_hook(int keycode, t_so_long *sl)
{
	(void)sl;
	if (keycode == KEY_ESC) // NOTE: WSLだと一度目のESCは認識されない（別の何かに吸われてる？)
		exit(EXIT_SUCCESS);
	return (0);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_so_long sl;

	sl_init(&sl);
	mlx_hook(sl.win, 33, 1L << 17, close_btn_hook, &sl);
	mlx_hook(sl.win, KeyPress, KeyPressMask, key_press_hook, &sl);
	mlx_loop_hook(sl.mlx, main_loop, &sl);
	mlx_loop(sl.mlx);
}