/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/09/18 00:34:52 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

op_tab =
	{
		{1, "live", 1, {T_DIR}, 10, "alive", 0, 0},
		{2, "ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 1},
		{3, "st", 2, {T_REG, T_IND | T_REG}, 5, 1, 0},
		{4, "add", 3, {T_REG, T_REG, T_REG}, 10, 1, 1},
		{5, "sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 1},
		{6, "and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1},
		{7, "or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1},
		{8, "xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 1},
		{9, "zjmp", 1, {T_DIR}, 20, 0, 0},
		{10, "ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 0},
		{11, "sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 0},
		{12, "fork", 1, {T_DIR}, 800, 0, 0},
		{13, "lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 1},
		{14, "lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 1},
		{15, "lfork", 1, {T_DIR}, 1000, 0, 0},
		{16, "aff", 1, {T_REG}, 2, 1, 0},
};
