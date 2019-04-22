/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_dylib.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:39:40 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/22 16:29:33 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

struct s_dylib				*get_macho_dylib_index(
		struct s_macho *const macho,
		const int index)
{
	int						count;
	struct s_dylib			*ptr;

	count = 0;
	ptr = macho->dylibs;
	while (ptr)
	{
		if (count++ == index)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

static inline void			fill_macho_dylib(
		struct s_loadcommand *const lc,
		struct s_dylib *const dylib)
{
	char					*bptr;

	dylib->lc = lc;
	dylib->path = ((char*)lc->content) + sizeof(struct dylib_command);
	bptr = dylib->path;
	while (*bptr)
		bptr++;
	while (*bptr != '/' && bptr > dylib->path)
		--bptr;
	dylib->name = ++bptr;
}

void						get_macho_dylib(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const lc)
{
	struct s_dylib *const	dylib = ft_memalloc(sizeof(struct s_dylib));
	struct s_dylib			*ptr;

	if (!dylib)
		return (set_error(binary, MRERR_MACHO));
	++macho->dylibs_count;
	if (!macho->dylibs)
	{
		macho->dylibs = dylib;
		fill_macho_dylib(lc, dylib);
	}
	else
	{
		ptr = macho->dylibs;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = dylib;
		fill_macho_dylib(lc, ptr);
	}
}
