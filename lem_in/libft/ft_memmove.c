/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:00:11 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/04 21:15:29 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char *s;
	char *d;

	s = (char*)src;
	d = (char*)dst;
	if (s > d)
		ft_strncpy(d, s, n);
	while (s < d && n)
	{
		d[n - 1] = s[n - 1];
		n--;
	}
	return (dst);
}
