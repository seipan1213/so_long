#ifndef SO_LONG_H
#define SO_LONG_H

#include "../minilibx-linux/mlx.h"
#include <X11/X.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define TITLE "SO_LONG"
#define WIDTH 600
#define HEIGHT 480

#define KEY_ESC 65307
#define KEY_LEFT_ARROW 65361
#define KEY_UP_ARROW 65362
#define KEY_RIGHT_ARROW 65363
#define KEY_DOWN_ARROW 65364

#define MALLOC_ERROR "malloc error"
#define MAP_ERROR "Error"

typedef enum e_err_type
{
	ERR_MALLOC,
	ERR_MAP
} t_err_type;

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_img;

typedef struct s_so_long
{
	void *mlx;
	void *win;
	t_img img;
} t_so_long;

int create_trgb(int t, int r, int g, int b);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);

int close_win(int keycode, t_so_long *sl);
t_so_long *sl_init();

size_t ft_strlen(char *str);
void put_exit_err(int type);

#endif
