/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:04:55 by souarrak          #+#    #+#             */
/*   Updated: 2019/05/19 14:19:14 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int			i;
	long		nb;
	long		nb1;
	int			neg;

	i = 0;
	neg = 1;
	nb1 = -1;
	nb = 0;
	while (str[i] == '0' || ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		neg = str[i++] == '-' ? -1 : 1;
	while (str[i] == '0')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb = (nb * 10) + ((long)str[i] - '0');
		if (nb <= nb1)
			return (neg == 1 ? -1 : 0);
		nb1 = nb;
		i++;
	}
	return (nb * neg);
}
