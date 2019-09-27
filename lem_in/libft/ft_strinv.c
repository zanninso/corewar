/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:46:38 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/05 00:42:34 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinv(char *str)
{
	int		j;
	int		k;
	char	*s;

	j = 0;
	k = ft_strlen(str) - 1;
	if (!(s = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (k >= 0)
	{
		s[j] = str[k];
		j++;
		k--;
	}
	s[j] = '\0';
	ft_strncpy(str, s, ft_strlen(str) + 1);
	free(s);
	return (str);
}
