/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:27:45 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/21 16:16:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static inline void		sort_symbols_swap(
		struct s_symbol *const a,
		struct s_symbol *const b)
{
	struct s_symbol	c;

	c.section = a->section;
	c.name = a->name;
	a->section = b->section;
	a->name = b->name;
	b->section = c.section;
	b->name = c.name;
}

static int				sort_symbols_partitionner(
		struct s_symbol *const symbols,
		int (*const sortfunc)(struct s_symbol *const a, struct s_symbol *const b),
		int p, int r)
{
	int					pivot;

	pivot = p;
	while (42)
	{
		while (sortfunc(symbols + r, symbols + pivot))
			--r;
		while (!sortfunc(symbols + p, symbols + pivot))
			++p;
		if (p < r)
			sort_symbols_swap(symbols + p, symbols + r);
		else
			return r;
	}
}

static void				sort_symbols_proc(
		struct s_symbol *const symbols,
		int (*const sortfunc)(struct s_symbol *const a, struct s_symbol *const b),
		int p, int r)
{
	int					q;

	if (p < r)
	{
		q = sort_symbols_partitionner(symbols, sortfunc, p, r);
		sort_symbols_proc(symbols, sortfunc, p, q);
		sort_symbols_proc(symbols, sortfunc, q + 1, r);
	}
}

void					sort_symbols(
		struct s_symbol *const symbols,
		const int count,
		int (*const sortfunc)(struct s_symbol *const a, struct s_symbol *const b))
{
	sort_symbols_proc(symbols, sortfunc, 0, count - 1);
}
