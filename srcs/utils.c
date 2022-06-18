#include "so_long.h"

size_t ft_strlen(char *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void put_exit_err(int type)
{
	if (type == ERR_MALLOC)
		write(STDERR_FILENO, MALLOC_ERROR, ft_strlen(MALLOC_ERROR));
	else if (type == ERR_MAP)
		write(STDERR_FILENO, MAP_ERROR, ft_strlen(MAP_ERROR));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}