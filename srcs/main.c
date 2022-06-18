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

void game_init(t_so_long *sl)
{
	int i;
	int j;

	sl->gm.width = 10; // ft_strlen(gnlline);
	sl->gm.height = 8; // list.cnt
	sl->gm.item_sum = 0;
	return; // TODO: MAP作成処理
	sl->gm.map = (int **)malloc(sizeof(int *) * sl->gm.height);
	i = 0;
	while (i < sl->gm.height)
	{
		sl->gm.map[i] = (int *)malloc(sizeof(int) * sl->gm.width);
		j = 0;
		while (j < sl->gm.width)
		{
			sl->gm.map[i][j] = 1;
			j++;
			if (sl->gm.map[i][j] == 1)
				sl->gm.item_sum++;
		}
		i++;
	}
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

int main_loop(t_so_long *sl)
{
	(void)sl;
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