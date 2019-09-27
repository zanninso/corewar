/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souarrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:10:48 by souarrak          #+#    #+#             */
/*   Updated: 2019/03/29 20:47:25 by souarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t size)
{
	t_list *list;

	list = NULL;
	list = (t_list*)ft_memalloc(sizeof(*list));
	if (list != NULL)
	{
		list->next = NULL;
		list->content_size = 0;
		if (content != NULL)
		{
			list->content = (void*)ft_memalloc(sizeof(*content) * (size + 1));
			if (list->content != NULL)
				ft_memcpy((list->content), content, size);
			list->content_size = size;
		}
	}
	return (list);
}
