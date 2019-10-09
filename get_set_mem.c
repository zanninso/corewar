/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:32:47 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/10/09 23:41:18 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int get_mem(unsigned char *mem, int oct)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	while (i < oct)
		ret = (ret << 8) + mem[i];
	return (ret);
}

void set_mem(unsigned char *mem, int val, int oct)
{
	int i;

	i = 0;
	while (i < oct) 
    {
		mem[i] = val >> (oct - i - 1);
		i++;
	}
}