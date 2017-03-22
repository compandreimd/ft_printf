/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:31:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 12:31:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_bool				get_dot(char *c, const char **fmt,
						t_printf *env, va_list *argp)
{
	if (isdigit(*c))
	{
		while (isdigit(*c))
		{
			env->prec = 10 * env->prec + CTOD(*c);
			*c = *++*fmt;
		}
		--*fmt;
	}
	else if (*c == '*')
	{
		env->prec = va_arg(*argp, int);
	}
	else
		return (false);
	return (true);
}
