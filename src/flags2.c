/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:22:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 12:22:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		get_of(t_printf *env)
{
	if (env->flags & INTMAXT)
		env->of = sizeof(intmax_t);
	else if (env->flags & SIZET)
		env->of = sizeof(size_t);
	else if (env->flags & PTRDIFFT || env->flags & LONGINT)
		env->of = sizeof(long);
	else if (env->flags & LLONGINT || env->flags & LONGDBL)
		env->of = sizeof(long long);
	else if (env->flags & SHORTINT)
		env->of = sizeof(short);
	else if (env->flags & CHARINT)
		env->of = sizeof(char);
	else
		env->of = sizeof(int);
}

void			get_int(t_printf *env, va_list *argp)
{
	if (env->flags & INTMAXT)
		env->ll = va_arg(*argp, intmax_t);
	else if (env->flags & SIZET)
		env->ll = va_arg(*argp, size_t);
	else if (env->flags & PTRDIFFT || env->flags & LONGINT)
		env->ll = va_arg(*argp, long);
	else if (env->flags & LLONGINT || env->flags & LONGDBL)
		env->ll = va_arg(*argp, long long);
	else if (env->flags & SHORTINT)
		env->ll = (short)va_arg(*argp, int);
	else if (env->flags & CHARINT)
		env->ll = (signed char)va_arg(*argp, int);
	else
		env->ll = va_arg(*argp, int);
	get_of(env);
}

static void		pas51(t_printf env)
{
	void *ptr;

	if (env.flags & INTMAXT)
		*(intmax_t *)ptr = env.np;
	else if (env.flags & LONGINT)
		*(long *)ptr = env.np;
	else if (env.flags & SHORTINT)
		*(short *)ptr = (short)env.np;
	else if (env.flags & CHARINT)
		*(unsigned char *)ptr = (unsigned char)env.np;
	else
		*(int *)ptr = env.np;
}

int				pas5(char c, t_printf env,
					va_list *argp)
{
	void *ptr;

	if (c == 'n')
	{
		ptr = va_arg(*argp, void *);
		if (ptr == NULL)
			return (0);
		else if (env.flags & LLONGINT)
			*(long long *)ptr = env.np;
		else if (env.flags & SIZET)
			*(ssize_t *)ptr = (ssize_t)env.np;
		else if (env.flags & PTRDIFFT)
			*(long *)ptr = env.np;
		else
			pas51(env);
		return (0);
	}
	return (-100);
}
