/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 15:04:55 by souarrak          #+#    #+#             */
/*   Updated: 2019/08/06 23:23:01 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *s)
{
	long long	n;
	int			m;
	int			i;

	n = 0;
	i = 0;
	m = 1;
	while (ft_iswhitespace(*s) || *s == 48 || ((*s == 45 || *s == 43)
	&& ft_isdigit(s[1])))
		m *= (*s++ == '-' ? -1 : 1);
	while (i++ < 19 && ft_isdigit(*s))
		n = (n * 10) + (*s++ - '0');
	return (n * m);
}
