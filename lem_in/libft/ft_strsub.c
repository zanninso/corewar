/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:00:05 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/07 15:46:02 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *dst;

	if (!s)
		return (NULL);
	if ((dst = (char *)ft_memalloc(sizeof(char) * (len + 1))))
	{
		ft_strncpy(dst, s + start, len);
		return (dst);
	}
	return (NULL);
}
