/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:22:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 12:22:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../includes/ft_printf.h"

static size_t	all_size(wchar_t *wstr)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (wstr[i])
	{
		n += ft_utf8chrsize(ft_utf8chrencode(wstr[i]));
		i++;
	}
	return (n);
}

static t_printf	set_env(t_printf env, char *cp)
{
	if (env.prec >= 0)
		env.size = ft_strnlen(cp, env.prec);
	else
		env.size = ft_strlen(cp);
	env.sign = '\0';
	env.free = true;
	return (env);
}

static int		do_while(wchar_t *wstr, char **cp, size_t n, int i)
{
	wchar_t		c;
	int			j;

	j = 0;
	c = ft_utf8chrencode(wstr[i]);
	while (j < ft_utf8chrsize(c))
	{
		cp[0][n + j] = ((char*)&c)[j];
		j++;
	}
	return (j);
}

int				print_wstr(int fd, t_printf env, wchar_t *wstr)
{
	char	*cp;
	int		i;
	int		j;
	size_t	n;

	if (!wstr)
		wstr = L"(null)";
	cp = malloc(all_size(wstr) + 1);
	i = 0;
	n = 0;
	while (wstr[i])
	{
		j = do_while(wstr, &cp, n, i);
		n += j;
		if (n > (unsigned)env.prec)
		{
			n -= j;
			break ;
		}
		i++;
	}
	cp[n] = '\0';
	env = set_env(env, cp);
	return (print_all(fd, env, cp));
}
