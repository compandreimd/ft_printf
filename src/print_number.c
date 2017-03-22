/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:26:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 14:26:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		dec(unsigned long uval, char **cp)
{
	*--*cp = DTOC(uval % 10);
	uval /= 10;
	while (uval)
	{
		*--*cp = DTOC(uval % 10);
		uval /= 10;
	}
}

static void		octo(unsigned long uval, char **cp, t_printf env)
{
	*--*cp = DTOC(uval & 7);
	uval >>= 3;
	while (uval)
	{
		*--*cp = DTOC(uval & 7);
		uval >>= 3;
	}
	if (env.flags & ALT && **cp != '0')
		*--*cp = '0';
}

static void		hex(unsigned long uval, char **cp, const char *xdigs)
{
	*--*cp = xdigs[uval & 15];
	uval >>= 4;
	while (uval)
	{
		*--*cp = xdigs[uval & 15];
		uval >>= 4;
	}
}

static char		*ltoa(char *endp, t_printf env, const char *xdigs)
{
	char			*cp;
	unsigned long	uval;

	cp = endp;
	uval = env.ll;
	if (env.of == 1)
		uval &= 0xff;
	else if (env.of == 2)
		uval &= 0xffff;
	else if (env.of == 4)
		uval &= 0xffffffff;
	if (env.base == 10)
		dec(uval, &cp);
	else if (env.base == 8)
		octo(uval, &cp, env);
	else if (env.base == 16)
		hex(uval, &cp, xdigs);
	return (cp);
}

int				print_number(int fd, t_printf env)
{
	char	*cp;
	char	buf[BUF];
	char	*xdigs;

	if (env.up)
		xdigs = "0123456789ABCDEF";
	else
		xdigs = "0123456789abcdef";
	if ((env.dprec = env.prec) >= 0)
		env.flags &= ~ZEROPAD;
	cp = buf + BUF;
	if (env.ll != 0 || env.prec != 0 || (env.flags & ALT && env.base == 8))
	{
		cp = ltoa(cp, env, xdigs);
	}
	env.size = buf + BUF - cp;
	return (print_all(fd, env, cp));
}
