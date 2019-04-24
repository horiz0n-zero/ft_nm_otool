/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_statics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 09:46:28 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/24 10:00:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static inline void		sort_statics_swap(
		struct s_staticlib_macho *const a,
		struct s_staticlib_macho *const b)
{
	const char *const	name = a->name;
	void *const			ran = a->ran;
	void *const			macho = a->macho;

	a->name = b->name;
	a->ran = b->ran;
	a->macho = b->macho;
	b->name = name;
	b->ran = ran;
	b->macho = macho;
}

static inline void				sort_statics_fill(
		struct s_staticlib_macho *f,
		struct s_staticlib_macho **statics)
{
	while (f)
	{
		*statics++ = f;
		f = f->next;
	}
}

void							sort_statics(
		struct s_staticlib_macho *const f,
		const int count)
{

	int							i;
	int							j;
	int							space;
	struct s_staticlib_macho	*statics[count];

	sort_statics_fill(f, statics);
	space = count / 2;
	i = 0;
	j = space;
	while (j > 0)
	{
		while (j < count)
		{
			if ((ptrdiff_t)statics[i]->macho->header > (ptrdiff_t)statics[j]->macho->header)
				sort_statics_swap(statics[i], statics[j]);
			i++;
			j++;
		}
		i = 0;
		j = --space;
	}
}
