/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:00:05 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/01 22:22:09 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *dst;

	dst = NULL;
	dst = (char*)ft_memalloc(sizeof(char) * (len + 1));
	if (s && dst)
	{
		ft_strncpy(dst, s + start, len);
		return (dst);
	}
	return (NULL);
}
