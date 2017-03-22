/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:26:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 14:26:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h>

int		print_str(int fd, t_printf env, char *str)
{
	if (str == 0)
		str = "(null)";
	if (env.prec >= 0)
		env.size = ft_strnlen(str, env.prec);
	else
		env.size = ft_strlen(str);
	env.sign = '\0';
	return (print_all(fd, env, str));
}
