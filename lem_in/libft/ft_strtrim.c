/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:37:44 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/01 22:43:19 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int i;
	int j;

	i = 0;
	if (s)
	{
		j = ft_strlen(s) - 1;
		while (ft_strlen(s) && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i++;
		while (ft_strlen(s) && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
			j--;
		return (ft_strsub(s, i, (j + 1 - i) >= 0 ? (j + 1 - i) : 0));
	}
	return (NULL);
}
