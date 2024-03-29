/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:06:51 by souarrak          #+#    #+#             */
/*   Updated: 2019/05/19 14:17:04 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_pow(long long n, int p)
{
	long long ret;
	long long m;

	ret = 1;
	m = n;
	while (p)
	{
		ret *= p & 1 ? m : 1;
		m *= m;
		p >>= 1;
	}
	return (ret);
}
