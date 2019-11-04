/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:04:02 by souarrak          #+#    #+#             */
/*   Updated: 2019/04/04 22:06:58 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list;
	t_list *ptr;

	list = f(lst);
	ptr = list;
	while (lst && lst->next)
	{
		list->next = f(lst->next);
		list = list->next;
		lst = lst->next;
	}
	return (ptr);
}
