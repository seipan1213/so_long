#include "so_long.h"

void put_exit_err(int type)
{
	if (type == ERR_MALLOC)
		write(STDERR_FILENO, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
	else if (type == ERR_MAP)
		write(STDERR_FILENO, MAP_ERROR, ft_strlen(MAP_ERROR));
	else if (type == ERR_MLX)
		write(STDERR_FILENO, MLX_ERROR, ft_strlen(MLX_ERROR));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}