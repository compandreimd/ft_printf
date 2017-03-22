/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:22:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 12:22:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		pas2(char c, int fd, t_printf env, va_list *argp)
{
	if (c == '%')
		return (print_char(fd, env, '%'));
	if (c == 'c' || c == 'C')
	{
		if (c == 'C')
			env.flags |= LONGINT;
		if (env.flags & LONGINT)
			return (print_wchar(fd, env, va_arg(*argp, wint_t)));
		else
			return (print_char(fd, env, va_arg(*argp, int)));
	}
	if (c == 's' || c == 'S')
	{
		if (c == 'S')
			env.flags |= LONGINT;
		if (env.flags & LONGINT)
			return (print_wstr(fd, env, va_arg(*argp, wchar_t*)));
		else
			return (print_str(fd, env, va_arg(*argp, char*)));
	}
	return (-100);
}

int		pas3(char c, int fd, t_printf env, va_list *argp)
{
	if (c == 'd' || c == 'i' || c == 'D' || c == 'u' || c == 'U')
	{
		if (c == 'D' || c == 'U')
			env.flags |= LONGINT;
		env.base = 10;
		get_int(&env, argp);
		if (c == 'u' || c == 'U')
			env.sign = '\0';
		else if (env.ll < 0)
		{
			env.sign = '-';
			env.ll = -env.ll;
		}
		return (print_number(fd, env));
	}
	if (c == 'o' || c == 'O')
	{
		if (c == 'O')
			env.flags |= LONGINT;
		get_int(&env, argp);
		env.base = 8;
		env.sign = '\0';
		return (print_number(fd, env));
	}
	return (-100);
}

int		pas4(char c, int fd, t_printf env, va_list *argp)
{
	if (c == 'p')
	{
		env.ll = (long long)va_arg(*argp, void*);
		env.base = 16;
		env.flags |= LONGINT;
		env.of = sizeof(void*);
		env.ox[1] = 'x';
		env.sign = '\0';
		return (print_number(fd, env));
	}
	if (c == 'x' || c == 'X')
	{
		if (c == 'X')
			env.up = true;
		get_int(&env, argp);
		env.base = 16;
		if (env.flags & ALT && env.ll)
			env.ox[1] = c;
		env.sign = '\0';
		return (print_number(fd, env));
	}
	return (-100);
}

int		flags(int fd, t_printf env, va_list *argp, char c)
{
	int i;

	i = 0;
	i = pas2(c, fd, env, argp);
	if (i > -10)
		return (i);
	i = pas3(c, fd, env, argp);
	if (i > -10)
		return (i);
	i = pas4(c, fd, env, argp);
	if (i > -10)
		return (i);
	i = pas5(c, env, argp);
	if (i > -10)
		return (i);
	if (c == '\0')
	{
		--*env.fmt;
		return (0);
	}
	return (print_char(fd, env, c));
}
