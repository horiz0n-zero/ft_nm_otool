/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:27:45 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/24 09:45:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static inline void		sort_symbols_swap(
		struct s_symbol *const a,
		struct s_symbol *const b)
{
	register uint64_t	*aptr;
	register uint64_t	*bptr;
	int					size;

	size = 0;
	aptr = (uint64_t*)a;
	bptr = (uint64_t*)b;
	while (size < (sizeof(struct s_symbol) / sizeof(uint64_t)))
	{
		*aptr ^= *bptr;
		*bptr ^= *aptr;
		*aptr++ ^= *bptr++;
		++size;
	}
}

static void				sort_symbols_reverse(
		struct s_symbol *const symbols,
		const int count)
{
	int					s;
	int					e;
	const int			middle = count / 2;

	s = 0;
	e = count - 1;
	while (s < middle)
	{
		sort_symbols_swap(symbols + s, symbols + e);
		++s;
		--e;
	}
}

void					sort_symbols(
		struct s_symbol *const symbols,
		const int count,
		const int reverse,
		int (*const sortfunc)(struct s_symbol *const a, struct s_symbol *const b))
{
	int					i;
	int					j;
	int					space;

	if (!sortfunc)
		return ;
	space = count / 2;
	i = 0;
	j = space;
	while (j > 0)
	{
		while (j < count)
		{
			if (sortfunc(symbols + i, symbols + j))
				sort_symbols_swap(symbols + i, symbols + j);
			i++;
			j++;
		}
		i = 0;
		j = --space;
	}
	if (reverse)
		sort_symbols_reverse(symbols, count);
}
