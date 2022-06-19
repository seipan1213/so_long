#include "so_long.h"

size_t ft_strlen(char *str)
{
	size_t len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void ft_bzero(void *s, size_t len)
{
	unsigned char *str;

	str = (unsigned char *)s;
	while (len--)
		str[len] = '\0';
}

void ft_putnbr_fd(int n, int fd)
{
	char c;

	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
	write(fd, "\n", 1);
}

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