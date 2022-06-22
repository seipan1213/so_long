#include "so_long.h"

void put_exit_err(int type)
{
	if (type == ERR_MALLOC)
		ft_putendl_fd(MALLOC_ERROR, STDERR_FILENO);
	else if (type == ERR_MAP)
		ft_putendl_fd(MAP_ERROR, STDERR_FILENO);
	else if (type == ERR_MLX)
		ft_putendl_fd(MLX_ERROR, STDERR_FILENO);
	else if (type == ERR_ARG)
		ft_putendl_fd(ARG_ERR, STDERR_FILENO);
	else if (type == ERR_FILE)
		ft_putendl_fd(FILE_ERR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int map_type(char c)
{
	if (c == '0')
		return (SP);
	else if (c == '1')
		return (WALL);
	else if (c == 'E')
		return (GOAL);
	else if (c == 'C')
		return (ITEM);
	else if (c == 'P')
		return (PL);
	put_exit_err(ERR_FILE);
	return (-1);
}

t_ipair *make_ipair(int i, int j)
{
	t_ipair *p;

	p = (t_ipair *)malloc(sizeof(t_ipair));
	p->first = i;
	p->second = j;
	return (p);
}