/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 12:35:42 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/05/21 18:09:27 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H
# include "../libft.h"
# define LEN 11454

typedef	struct	s_bigint
{
	char		nb[LEN + 1];
	bool		sign;
	int			len;
}				t_bigint;

typedef struct	s_multpvariable
{
	int			r;
	bool		sign;
	t_bigint	m;
	t_bigint	ret;
}				t_multpvariable;

t_bigint		ar_op(t_bigint op1, char c, t_bigint op2);
bool			cn_op(t_bigint op1, char *s, t_bigint op2);
void			bi_assing(t_bigint *op, long long n);
void			bi_init(t_bigint *op, long long n);
t_bigint		bi_copy(t_bigint *op1, t_bigint op2);
t_bigint		ft_bipow(t_bigint n, int p);
void			bi_move(t_bigint *m, unsigned int i);

#endif
