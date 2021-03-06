/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:29:04 by sehattor          #+#    #+#             */
/*   Updated: 2022/04/12 20:00:55 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*memory;
	size_t			len;

	len = size * count;
	memory = (unsigned char *)malloc(len);
	if (!memory)
		return (NULL);
	while (len--)
		memory[len] = 0;
	return ((void *)(memory));
}
