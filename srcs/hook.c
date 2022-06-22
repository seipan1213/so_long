#include "so_long.h"

int close_btn_hook(int keycode, t_so_long *sl)
{
	(void)sl;
	(void)keycode;
	exit(EXIT_FAILURE);
}

int key_press_hook(int keycode, t_so_long *sl)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	else if (keycode == KEY_W)
		player_move(sl, UP);
	else if (keycode == KEY_S)
		player_move(sl, DOWN);
	else if (keycode == KEY_D)
		player_move(sl, RIGHT);
	else if (keycode == KEY_A)
		player_move(sl, LEFT);
	return (0);
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