/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gayoub <gayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:32:07 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/07 03:03:19 by gayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		ft_set_flags(const char *str, _Bool *flags,
								const char *acpt_flgs, void (*f)(char, _Bool*))
{
	if (!str || *str++ != '-' || *str == '-' || !ft_isprint(*str))
		return (0);
	while (*str)
	{
		if (ft_isinstr(*str, acpt_flgs) || (!acpt_flgs && ft_isalnum(*str)))
		{
			flags[(int)*str] = 1;
			if (f)
				f(*str, flags);
		}
		else
			return (-1);
		str++;
	}
	return (1);
}

void		ft_unset_flags(int c, _Bool *flags)
{
	flags[c] = 0;
}

_Bool		ft_flag_active(int c, _Bool *flags)
{
	return (flags[c]);
}
