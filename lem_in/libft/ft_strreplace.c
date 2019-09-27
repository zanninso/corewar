/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <souarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 23:28:56 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/07 11:57:09 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *str, char to_find, char c)
{
	if (!str)
		return (NULL);
	str = ft_strchr(str, to_find);
	if (str)
		*str++ = c;
	return (str);
}
