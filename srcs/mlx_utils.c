#include "so_long.h"

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

size_t pic_color(t_img img, int x, int y)
{
	if (0 <= x && x < img.width && 0 <= y && y <= img.height)
		return (*((unsigned int *)(img.addr + y * img.llen) + x));
	else
		return (0);
}