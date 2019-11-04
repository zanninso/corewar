/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:20:25 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/04 21:17:25 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*ptr;

	i = 0;
	str = (unsigned char*)s;
	ptr = NULL;
	while (i < n)
	{
		if (str[i] == (unsigned char)(c))
		{
			ptr = str + i;
			return ((void*)ptr);
		}
		i++;
	}
	return ((void*)ptr);
}
