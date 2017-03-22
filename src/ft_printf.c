/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 12:20:02 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/21 12:20:05 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../includes/ft_printf.h"

static int		do_print(int fd, const char *fmt, va_list *argp)
{
	char		c;
	int			np;
	t_printf	env;

	np = 0;
	while ((c = *fmt) != '\0')
	{
		if (c == '%')
		{
			env = get_env(&fmt, &c, argp);
			env.np = np;
			env.fmt = &fmt;
			np += flags(fd, env, argp, c);
		}
		else
		{
			write(fd, &c, 1);
			np++;
		}
		fmt++;
	}
	return (np);
}

int				ft_printf(const char *fmt, ...)
{
	va_list		list;
	int			len;

	len = 0;
	if (fmt)
	{
		va_start(list, fmt);
		len = do_print(1, fmt, &list);
		va_end(list);
	}
	return (len);
}

int				ft_fprintf(int fd, const char *fmt, ...)
{
	va_list		list;
	int			len;

	len = 0;
	if (fmt)
	{
		va_start(list, fmt);
		len = do_print(fd, fmt, &list);
		va_end(list);
	}
	return (len);
}
