/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:38:40 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/05 19:02:06 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_char(char const *str, int i, char c)
{
	int count;

	count = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**str;
	unsigned int	i;
	unsigned int	j;

	str = (char**)malloc(sizeof(char*) * (ft_count_words(s, c) + 1));
	if (!s || !str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break ;
		if (!(str[j] = ft_strsub(s, i, nb_char(s, i, c))))
			return (0);
		j++;
		while (s[i] != c && s[i])
			i++;
	}
	str[j] = NULL;
	return (str);
}
