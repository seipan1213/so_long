#include "so_long.h"

int close_btn_hook(int keycode, t_so_long *sl)
{
	(void)sl;
	(void)keycode;
	exit(EXIT_FAILURE);
}

void sl_init(t_so_long *sl, char *file_path)
{
	ft_bzero(sl, sizeof(t_so_long));
	view_init(sl);
	imgs_init(sl);
	game_init(sl, file_path);
}

void line_to_map(t_so_long *sl, char *line)
{
	(void)sl;
	(void)line;
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

void set_type(t_so_long *sl, int type, int x, int y)
{
	if (type == PL)
	{
		sl->gm.pl.x = x;
		sl->gm.pl.y = y;
	}
	else if (type == ITEM)
		sl->gm.item_sum++;
}

void conv_map(t_so_long *sl, t_dc_lst *map)
{
	int y;
	int x;

	sl->gm.map = malloc(sizeof(int *) * sl->gm.height);
	if (sl->gm.map == NULL)
		put_exit_err(ERR_MALLOC);
	map = get_first_lst(map);
	y = -1;
	while (++y < sl->gm.height)
	{
		sl->gm.map[y] = malloc(sizeof(int) * sl->gm.width);
		if (sl->gm.map[y] == NULL)
			put_exit_err(ERR_MALLOC);
		x = -1;
		while (++x < sl->gm.width)
		{
			set_type(sl, map_type(map->value[x]), x, y);
			sl->gm.map[y][x] = map_type(map->value[x]);
		}
		map = map->next;
	}
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
	clear_lst(map);
}

void game_init(t_so_long *sl, char *file_path)
{
	map_init(sl, file_path);
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

void game_clear()
{
	ft_putendl_fd("CLEAR", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void player_move(t_so_long *sl, int vec_type)
{
	int next_px;
	int next_py;

	next_px = sl->gm.pl.x;
	next_py = sl->gm.pl.y;
	if (vec_type == UP)
		next_py--;
	else if (vec_type == DOWN)
		next_py++;
	else if (vec_type == RIGHT)
		next_px++;
	else if (vec_type == LEFT)
		next_px--;
	if (sl->gm.map[next_py][next_px] == GOAL && sl->gm.item_sum == sl->gm.pl.get_item)
		game_clear();
	if (sl->gm.map[next_py][next_px] != SP && sl->gm.map[next_py][next_px] != ITEM)
		return;
	if (sl->gm.map[next_py][next_px] == ITEM)
		sl->gm.pl.get_item++;
	sl->gm.map[next_py][next_px] = PL;
	sl->gm.map[sl->gm.pl.y][sl->gm.pl.x] = SP;
	sl->gm.pl.x = next_px;
	sl->gm.pl.y = next_py;
	ft_putnbr_fd(++sl->gm.move_cnt, STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
}

int key_press_hook(int keycode, t_so_long *sl)
{
	(void)sl;
	if (keycode == KEY_ESC) // NOTE: WSLだと一度目のESCは認識されない（別の何かに吸われてる？)
		exit(EXIT_SUCCESS);
	else if (keycode == KEY_UP_ARROW)
		player_move(sl, UP);
	else if (keycode == KEY_DOWN_ARROW)
		player_move(sl, DOWN);
	else if (keycode == KEY_RIGHT_ARROW)
		player_move(sl, RIGHT);
	else if (keycode == KEY_LEFT_ARROW)
		player_move(sl, LEFT);
	return (0);
}

void input_check(int argc, char **argv)
{
	size_t len;

	if (argc != 2)
		put_exit_err(ERR_ARG);
	len = ft_strlen(argv[1]);
	if (len <= 4 && ft_strncmp(&argv[1][len - 4], ".ber", 5))
		put_exit_err(ERR_ARG);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_so_long sl;

	input_check(argc, argv);
	sl_init(&sl, argv[1]);
	mlx_hook(sl.win, 33, 1L << 17, close_btn_hook, &sl);
	mlx_hook(sl.win, KeyPress, KeyPressMask, key_press_hook, &sl);
	mlx_loop_hook(sl.mlx, main_loop, &sl);
	mlx_loop(sl.mlx);
}