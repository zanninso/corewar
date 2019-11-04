/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 22:53:32 by souarrak          #+#    #+#             */
/*   Updated: 2019/05/19 16:36:57 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

long long			ft_va_arg(va_list ap, char type)
{
	if (type == '\0')
		return (va_arg(ap, int));
	if (type == 'h')
		return ((short)va_arg(ap, int));
	if (type == 'H')
		return ((char)va_arg(ap, int));
	if (ft_isinstr(type, "ljz"))
		return (va_arg(ap, long));
	if (type == 'I')
		return (va_arg(ap, long long));
	return (0);
}

unsigned long long	ft_uva_arg(va_list ap, char type)
{
	if (type == '\0')
		return (va_arg(ap, unsigned int));
	if (type == 'h')
		return ((unsigned short)va_arg(ap, unsigned int));
	if (type == 'H')
		return ((unsigned char)va_arg(ap, unsigned int));
	if (ft_isinstr(type, "ljz"))
		return (va_arg(ap, unsigned long));
	if (type == 'I')
		return (va_arg(ap, unsigned long long));
	return (0);
}

long double			ft_fva_arg(va_list ap, char type)
{
	if (type == '\0' || type == 'l' || type == 'j')
		return (va_arg(ap, double));
	if (type == 'L')
		return (va_arg(ap, long double));
	return (0);
}
