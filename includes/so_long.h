#ifndef SO_LONG_H
#define SO_LONG_H

#include "../minilibx-linux/mlx.h"
#include "libft.h"
#include <X11/X.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define TITLE "SO_LONG"
#define WIDTH 1200
#define HEIGHT 960

#define KEY_ESC 65307
#define KEY_LEFT_ARROW 65361
#define KEY_UP_ARROW 65362
#define KEY_RIGHT_ARROW 65363
#define KEY_DOWN_ARROW 65364

#define MALLOC_ERROR "MALLOC Error"
#define MAP_ERROR "Error"
#define MLX_ERROR "MLX Error"
#define ARG_ERR "ARG Error"

#define PLAYER_PATH "img/player.xpm"
#define ITEM_PATH "img/item.xpm"
#define GOAL_PATH "img/goal.xpm"
#define WALL_PATH "img/wall.xpm"

typedef enum e_err_type
{
	ERR_MALLOC,
	ERR_MAP,
	ERR_MLX,
	ERR_ARG
} t_err_type;

typedef enum e_vec_type
{
	UP,
	DOWN,
	RIGHT,
	LEFT
} t_vec_type;

typedef enum e_map_type
{
	SP,
	WALL,
	PL,
	GOAL,
	ITEM
} t_map_type;

typedef struct s_img
{
	void *img;
	char *addr;
	int width;
	int height;
	int bpp;
	int llen;
	int endian;
} t_img;

typedef struct s_player
{
	int x;
	int y;
	int get_item;
} t_player;

typedef struct s_vec2
{
	int x;
	int y;
} t_vec2;

typedef struct s_game_manager
{
	int width;
	int height;
	int s_width;
	int s_height;
	int **map;
	int item_sum;
	int move_cnt;
	size_t back_color;
	t_player pl;
} t_game_manager;

typedef struct s_so_long
{
	void *mlx;
	void *win;
	t_img win_img;
	t_img wall_img;
	t_img player_img;
	t_img goal_img;
	t_img item_img;
	t_game_manager gm;
} t_so_long;

int create_trgb(int t, int r, int g, int b);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
size_t pic_color(t_img img, int i, int j);

void put_exit_err(int type);

int close_btn_hook(int keycode, t_so_long *sl);
void sl_init(t_so_long *sl);
void view_init(t_so_long *sl);
void imgs_init(t_so_long *sl);
void read_img(t_so_long *sl, t_img *img, char *path);
int main_loop(t_so_long *sl);
int key_press_hook(int keycode, t_so_long *sl);
void game_init(t_so_long *sl);

#endif
