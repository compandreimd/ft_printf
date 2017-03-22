/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:22:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 12:22:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t count;

	count = 0;
	while (str[count])
	{
		count++;
	}
	return (count);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t len;

	len = 0;
	while (len < maxlen)
	{
		if (!*s)
			break ;
		len++;
		s++;
	}
	return (len);
}

int		pad(int fd, int size, char c)
{
	int n;

	n = 0;
	while (size > 0)
	{
		n += write(fd, &c, 1);
		size -= 1;
	}
	return (n);
}
