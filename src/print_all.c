/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 12:29:26 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/21 12:29:28 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/ft_printf.h"

static int		part(int fd, t_printf *env, int *realsize)
{
	int np;

	np = 0;
	if (env->dprec > env->size)
		*realsize = env->dprec;
	else
		*realsize = env->size;
	if (env->sign)
		(*realsize)++;
	if (env->ox[1])
		*realsize += 2;
	if ((env->flags & (LADJUST | ZEROPAD)) == 0)
		np += pad(fd, env->width - *realsize, ' ');
	if (env->sign)
		np += write(fd, &env->sign, 1);
	return (np);
}

int				print_all(int fd, t_printf env, char *cp)
{
	int realsize;
	int np;

	np = part(fd, &env, &realsize);
	if (env.ox[1])
	{
		env.ox[0] = '0';
		np += write(fd, env.ox, 2);
	}
	if ((env.flags & (LADJUST | ZEROPAD)) == ZEROPAD)
		np += pad(fd, env.width - realsize, '0');
	np += pad(fd, env.dprec - env.size, '0');
	np += write(fd, cp, env.size);
	if (env.flags & LADJUST)
		np += pad(fd, env.width - realsize, ' ');
	if (env.free)
	{
		free(cp);
	}
	return (np);
}
