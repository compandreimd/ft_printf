/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:22:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 12:22:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_printf		init(void)
{
	t_printf	rs;

	rs.flags = 0;
	rs.up = false;
	rs.dprec = 0;
	rs.width = 0;
	rs.prec = -1;
	rs.ox[1] = '\0';
	rs.sign = '\0';
	rs.expchar = '\0';
	rs.expt = 0;
	rs.decpt_len = 0;
	rs.free = false;
	return (rs);
}

static t_bool		get_env2(char *c, t_printf *env, va_list *argp)
{
	if (*c == ' ')
	{
		if (!env->sign)
			env->sign = ' ';
	}
	else if (*c == '#')
		env->flags |= ALT;
	else if (*c == '*')
	{
		env->width = va_arg(*argp, int);
		if (env->width < 0)
		{
			env->width = -env->width;
			env->flags |= LADJUST;
		}
	}
	else if (*c == '-')
		env->flags |= LADJUST;
	else if (*c == '+')
		env->sign = '+';
	else
		return (false);
	return (true);
}

static t_bool		get_env3(char *c, t_printf *env)
{
	if (*c == 'h')
	{
		if (env->flags & SHORTINT)
		{
			env->flags &= ~SHORTINT;
			env->flags |= CHARINT;
		}
		else
			env->flags |= SHORTINT;
	}
	else if (*c == 'l')
	{
		if (env->flags & LONGINT)
		{
			env->flags &= ~LONGINT;
			env->flags |= LLONGINT;
		}
		else
			env->flags |= LONGINT;
	}
	else
		return (false);
	return (true);
}

static t_bool		get_env4(char *c, const char **fmt, t_printf *env)
{
	if (*c == '0')
		env->flags |= ZEROPAD;
	else if (isdigit(*c))
	{
		env->width = 0;
		while (isdigit(*c))
		{
			env->width = 10 * env->width + CTOD(*c);
			*c = *++*fmt;
		}
		--*fmt;
	}
	else if (*c == 'j')
		env->flags |= INTMAXT;
	else if (*c == 'q')
		env->flags |= LLONGINT;
	else if (*c == 't')
		env->flags |= PTRDIFFT;
	else if (*c == 'z')
		env->flags |= SIZET;
	else
		return (false);
	return (true);
}

t_printf			get_env(const char **fmt, char *c, va_list *argp)
{
	t_printf	env;

	++*fmt;
	env = init();
	while (true)
	{
		*c = **fmt;
		if (!get_env2(c, &env, argp))
			if (!get_env3(c, &env))
				if (!get_env4(c, fmt, &env))
				{
					if (*c == '.')
					{
						env.prec = 0;
						*c = *++*fmt;
						if (!get_dot(c, fmt, &env, argp))
							break ;
					}
					else
						break ;
				}
		(*fmt)++;
	}
	return (env);
}
