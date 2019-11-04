/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:49:21 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/11 16:52:28 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, size_t size)
{
	char	*str;

	if (!ptr)
		return ((ptr = ft_strnew(size)));
	if ((str = ft_strnew(size)) == NULL)
		return (NULL);
	if (size >= ft_strlen(ptr))
	{
		ft_strncpy(str, ptr, ft_strlen(ptr));
		free(ptr);
		ptr = NULL;
		return (str);
	}
	if (size < ft_strlen(ptr))
	{
		ft_strncpy(str, ptr, size);
		free(ptr);
		ptr = NULL;
		return (str);
	}
	return (NULL);
}
