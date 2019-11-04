/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bipow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:35:17 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/05/21 17:33:42 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint	ft_bipow(t_bigint nb, int p)
{
	t_bigint	ret;
	t_bigint	m;
	t_bigint	one;

	p = ABS(p);
	bi_assing(&one, 1);
	bi_assing(&ret, 1);
	m = nb;
	while (p)
	{
		ret = ar_op(ret, '*', p & 1 ? m : one);
		if (p >>= 1)
			m = ar_op(m, '*', m);
	}
	return (ret);
}
