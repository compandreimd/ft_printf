/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalcoci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:26:00 by amalcoci          #+#    #+#             */
/*   Updated: 2017/03/20 14:26:00 by amalcoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_bool		ft_getendian(void)
{
	short		nbr;

	nbr = 1;
	return (*(char *)&nbr != 1);
}

int			print_wchar(int fd, t_printf env, wint_t c)
{
	wchar_t wchar;

	wchar = ft_utf8chrencode(c);
	env.size = ft_utf8chrsize(wchar);
	return (print_all(fd, env, (char *)&wchar));
}
