/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 11:44:30 by souarrak          #+#    #+#             */
/*   Updated: 2019/03/31 15:05:07 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;

	ptr = NULL;
	while (*alst)
	{
		ptr = (*alst)->next;
		ft_lstdelone(&(*alst), del);
		*alst = ptr;
	}
	*alst = NULL;
}
