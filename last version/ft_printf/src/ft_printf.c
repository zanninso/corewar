/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:11:18 by souarrak          #+#    #+#             */
/*   Updated: 2019/05/22 00:15:42 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_fmt(const char *fmt, va_list ap, va_list ap2, t_flg *flg)
{
	int	count;

	count = 0;
	while (*fmt)
	{
		if (*fmt == '{')
			fmt = set_color(fmt);
		else if (*fmt == '%')
		{
			fmt++;
			fmt = get_options(fmt, flg, ap, ap2);
			count = count + (dispatcher(ap, flg));
		}
		else
		{
			ft_putchar(*fmt);
			count++;
			fmt++;
		}
	}
	return (count);
}

int	ft_printf(const char *restrict fmt, ...)
{
	va_list	ap;
	va_list	ap2;
	t_flg	flg;

	if (!fmt)
		return (0);
	va_start(ap, fmt);
	va_start(ap2, fmt);
	return (print_fmt(fmt, ap, ap2, &flg));
}
