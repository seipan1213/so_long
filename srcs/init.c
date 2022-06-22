#include "so_long.h"

void sl_init(t_so_long *sl, char *file_path)
{
	ft_bzero(sl, sizeof(t_so_long));
	sl->mlx = mlx_init();
	if (!sl->mlx)
		put_exit_err(ERR_MLX);
	game_init(sl, file_path);
	imgs_init(sl);
	view_init(sl);
}

void game_init(t_so_long *sl, char *file_path)
{
	map_init(sl, file_path);
	sl->gm.s_width = WIDTH / sl->gm.width;
	sl->gm.s_height = HEIGHT / sl->gm.height;
	sl->gm.back_color = create_trgb(0, 62, 204, 96);
	return;
}

void map_init(t_so_long *sl, char *file_path)
{
	t_dc_lst *map;

	map = read_map(file_path);
	sl->gm.height = get_lst_size(map);
	sl->gm.width = ft_strlen(get_first_lst(map)->value);
	sl->gm.item_sum = 0;
	sl->gm.pl.x = -1;
	conv_map(sl, map);
	check_map(sl);
	clear_lst(map);
}

void view_init(t_so_long *sl)
{
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
	read_img(sl, &sl->player_1_img, PLAYER_1_PATH);
	read_img(sl, &sl->player_2_img, PLAYER_2_PATH);
	read_img(sl, &sl->goal_img, GOAL_PATH);
	read_img(sl, &sl->wall_img, WALL_PATH);
	read_img(sl, &sl->item_img, ITEM_PATH);
	read_img(sl, &sl->back_img, BACK_PATH);
}
