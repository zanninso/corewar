/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:15:35 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/05/20 20:29:02 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	declen_base(unsigned long long n, int base)
{
	int len;

	len = 1;
	while ((n = n / base))
		len++;
	return (len);
}

char		*ft_uitoa_base(unsigned long long n, int base)
{
	const char	*b;
	int			len;
	char		*res;

	b = "0123456789abcdef";
	len = declen_base(n, base);
	res = ft_strnew(len);
	if (!res)
		return (NULL);
	while (len--)
	{
		res[len] = b[n % base];
		n /= base;
	}
	return (res);
}
