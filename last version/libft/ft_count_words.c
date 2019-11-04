/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:57:22 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/05 18:58:48 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_count_words(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (!str[i])
			break ;
		count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}
