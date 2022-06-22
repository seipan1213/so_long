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
#define HEIGHT 800

#define KEY_ESC 65307
#define KEY_A 97
#define KEY_W 119
#define KEY_D 100
#define KEY_S 115

#define CLEAR_TEXT "CLEAR"

#define MALLOC_ERROR "Error\nMalloc failed"
#define MLX_ERROR "Error\nMlx failed"
#define ARG_ERR "Error\nInvalid arguments"
#define FILE_ERR "Error\nInvalid file"
#define MAP_NOT_RECT_ERR "Error\nMap: not rectangular"
#define MAP_MISSING_ERR "Error\nMap: E or C or P are missing"
#define MAP_NOT_ENCLOSED_ERR "Error\nMap: not enclosed by wall"
#define MAP_UN_KNOW_CHAR_ERR "Error\nMap: unknown character"
#define MAP_CANT_FINISH_ERR "Error\nMap: cant finish"

#define PLAYER_PATH "img/player.xpm"
#define ITEM_PATH "img/item.xpm"
#define GOAL_PATH "img/goal.xpm"
#define WALL_PATH "img/wall.xpm"

typedef enum e_err_type
{
	ERR_MALLOC,
	ERR_MLX,
	ERR_ARG,
	ERR_FILE,
	ERR_MAP_NOT_RECT,
	ERR_MAP_MISSING,
	ERR_MAP_NOT_ENCLOSED,
	ERR_MAP_UN_KNOW_CHAR,
	ERR_MAP_CANT_FINISH
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

typedef struct s_ipair
{
	int first;
	int second;
} t_ipair;

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

typedef struct s_dc_lst
{
	char *value;
	struct s_dc_lst *next;
	struct s_dc_lst *prev;
} t_dc_lst;

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

void draw_back(t_so_long *sl);
void draw_img(t_so_long *sl, t_img *img, int s_x, int s_y);
void draw_select_img(t_so_long *sl, int map_x, int map_y);
void draw_imgs(t_so_long *sl);

void read_img(t_so_long *sl, t_img *img, char *path);
t_dc_lst *read_map(char *file_path);

int close_btn_hook(int keycode, t_so_long *sl);
int key_press_hook(int keycode, t_so_long *sl);
void player_move(t_so_long *sl, int vec_type);
void game_clear(t_so_long *sl);

void sl_init(t_so_long *sl, char *file_path);
void game_init(t_so_long *sl, char *file_path);
void map_init(t_so_long *sl, char *file_path);
void view_init(t_so_long *sl);
void imgs_init(t_so_long *sl);

void dc_lst_addfront(t_dc_lst *lst, char *value);
void dc_lst_addback(t_dc_lst *lst, char *value);
t_dc_lst *dc_lst_init(void);
int get_lst_size(t_dc_lst *lst);
t_dc_lst *get_first_lst(t_dc_lst *lst);
void clear_lst(t_dc_lst *lst);
void delete_lst(t_dc_lst *lst);

void input_check(int argc, char **argv);

void check_map(t_so_long *sl);
void bfs_utils(t_so_long *sl, int **map, t_list **lst, int *item_sum);
void map_bfs(t_so_long *sl, int **map, t_ipair p);
void is_close_map(t_so_long *sl);
void bfs_clear(t_list **lst);
bool is_edge(t_so_long *sl, t_ipair p);

void set_type(t_so_long *sl, int type, int x, int y);
void conv_map(t_so_long *sl, t_dc_lst *map);
int map_type(char c);

int create_trgb(int t, int r, int g, int b);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
size_t pic_color(t_img img, int x, int y);

int update(t_so_long *sl);
void game_update(t_so_long *sl);

void put_exit_err(int type);
t_ipair *make_ipair(int i, int j);
#endif
