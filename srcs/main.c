#include "so_long.h"

int close_btn_hook(int keycode, t_so_long *sl)
{
	(void)sl;
	(void)keycode;
	exit(EXIT_FAILURE);
}

t_so_long *sl_init()
{
	t_so_long *sl;

	sl = malloc(sizeof(t_so_long));
	if (sl == NULL)
		put_exit_err(ERR_MALLOC);
	sl->mlx = mlx_init();
	if (!sl->mlx)
		put_exit_err(ERR_MALLOC);
	sl->win = mlx_new_window(sl->mlx, WIDTH, HEIGHT, TITLE);
	if (!sl->win)
		put_exit_err(ERR_MALLOC);
	sl->img.img = mlx_new_image(sl->mlx, WIDTH, HEIGHT);
	if (!sl->img.img)
		put_exit_err(ERR_MALLOC);
	sl->img.addr = mlx_get_data_addr(sl->img.img, &sl->img.bits_per_pixel,
									 &sl->img.line_length, &sl->img.endian);
	return (sl);
}

int main_loop(t_so_long *sl)
{
	(void)sl;
	mlx_put_image_to_window(sl->mlx, sl->win, sl->img.img, 0, 0);
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

	t_so_long *sl;

	sl = sl_init();
	mlx_hook(sl->win, 33, 1L << 17, close_btn_hook, sl);
	mlx_hook(sl->win, KeyPress, KeyPressMask, key_press_hook, sl);
	mlx_loop_hook(sl->mlx, main_loop, sl);
	mlx_loop(sl->mlx);
}