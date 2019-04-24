/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:55:16 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/23 09:39:10 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

int							sort_symbols_numeric(
		struct s_symbol *const a,
		struct s_symbol *const b)
{
	if (a->value > b->value)
		return (1);
	return (0);
}

int							sort_symbols_alpha(
		struct s_symbol *const a,
		struct s_symbol *const b)
{
	register char			*aptr;
	register char			*bptr;

	aptr = a->name;
	bptr = b->name;
	while (*aptr || *bptr)
	{
		if (*aptr != *bptr)
		{
			if (*aptr > *bptr)
				return (1);
			else
				return (0);
		}
		++aptr;
		++bptr;
	}
	return (0);
}
