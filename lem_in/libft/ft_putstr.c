/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:15:05 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/26 22:26:30 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *str)
{
	int i;

	i = 0;
	if (!str)
		ft_putstr("(null)");
	while (str && str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}