#include "so_long.h"

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
	mlx_loop_hook(sl.mlx, update, &sl);
	mlx_loop(sl.mlx);
}