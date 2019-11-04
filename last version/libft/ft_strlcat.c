/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 11:19:38 by souarrak          #+#    #+#             */
/*   Updated: 2019/03/30 21:32:56 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t n;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j])
		j++;
	n = i + j;
	j = 0;
	while (src[j] && size > i + 1)
	{
		dst[i] = src[j];
		i++;
		j++;
		if (src[j] == '\0' || i == size - 1)
		{
			dst[i] = '\0';
			break ;
		}
	}
	return (n);
}
