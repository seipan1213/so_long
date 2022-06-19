/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:19:23 by sehattor          #+#    #+#             */
/*   Updated: 2022/04/12 20:17:05 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_free(char *save)
{
	free(save);
	return (NULL);
}

char	*read_fd(int fd, char *save)
{
	char	*tmp;
	char	*buf;
	int		ret;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!check_buf_and_save(&buf, &save))
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(save, buf);
		if (save)
			free(save);
		save = tmp;
		if (!tmp || ft_strchr(save, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (ret < 0)
		return (save = save_free(save));
	return (save);
}

char	*save_line(char *save, char *line, int *ret)
{
	char	*tmp;

	tmp = ft_strchr(line, '\n');
	free(save);
	save = NULL;
	if (!tmp)
	{
		*ret = 0;
		return (NULL);
	}
	return (ft_strdup(tmp + 1));
}

char	*get_line(char *line)
{
	char	*tmp;

	tmp = ft_strchr(line, '\n');
	if (!tmp)
		return (line);
	*tmp = '\0';
	tmp = ft_strdup(line);
	free(line);
	line = NULL;
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	static char	*save[256];
	int			ret;

	ret = 1;
	if (0 > fd || fd > 256 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	if (save[fd] != NULL)
	{
		*line = ft_strdup(save[fd]);
		if (!(*line))
			return (-1);
		if (ft_strchr(*line, '\n'))
		{
			save[fd] = save_line(save[fd], *line, &ret);
			*line = get_line(*line);
			return (ret);
		}
	}
	*line = read_fd(fd, *line);
	if (!(*line))
		return (-1);
	save[fd] = save_line(save[fd], *line, &ret);
	*line = get_line(*line);
	return (ret);
}
