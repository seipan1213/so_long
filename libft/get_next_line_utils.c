/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:39:11 by sehattor          #+#    #+#             */
/*   Updated: 2022/04/12 20:17:13 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		s1_len;

	s1_len = 0;
	while (s1[s1_len] != '\0')
		s1_len++;
	dup = (char *)malloc(s1_len * sizeof(char) + 1);
	if (!dup)
		return (NULL);
	dup[s1_len] = '\0';
	while (s1_len--)
		dup[s1_len] = s1[s1_len];
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
	{
		if (s[cnt] == c)
			return ((char *)(s + cnt));
		cnt++;
	}
	if (s[cnt] == c)
		return ((char *)(s + cnt));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	str = (char *)malloc((i + j) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[i + j] = '\0';
	len = i;
	while (i--)
		str[i] = s1[i];
	while (j--)
		str[len + j] = s2[j];
	return (str);
}

int	check_buf_and_save(char **buf, char **save)
{
	if (!(*buf))
		return (0);
	if (!(*save))
	{
		*save = ft_strdup("\0");
		if (!(*save))
		{
			free(*buf);
			return (0);
		}
	}
	return (1);
}
