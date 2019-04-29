/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:32:16 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 09:39:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static inline char	get_nlist_extchar_type(
		struct s_symbol *const symbol,
		const int type)
{
	if (type == N_UNDF)
	{
		if (symbol->value)
			return ('c');
		return ('u');
	}
	else if (type == N_PBUD)
		return ('u');
	else if (type == N_ABS)
		return ('a');
	else if (symbol->section)
	{
		if (symbol->section->sectname[2] == 't')
			return ('t');
		else if (symbol->section->sectname[2] == 'd')
			return ('d');
		else if (symbol->section->sectname[2] == 'b')
			return ('b');
		return ('s');
	}
	else if (type == N_INDR)
		return ('i');
	return ('?');
}

char				get_nlist_extchar(struct s_symbol *const symbol)
{
	char			r;

	if (symbol->type & N_STAB)
		return ('-');
	else
		r = get_nlist_extchar_type(symbol, symbol->type & N_TYPE);
	if (symbol->type & N_EXT && r != '?')
		r -= 32;
	return (r);
}

static const char	*get_nlist_library_name(
		const char *name)
{
	static char		buffer[2048];
	char			*ptr;

	ptr = str_push(" (from ", buffer);
	while (*name)
		*ptr++ = *name++;
	*ptr++ = ')';
	*ptr = 0;
	return (buffer);
}

const char			*get_nlist_library(
		struct s_macho *const macho,
		struct s_symbol *const symbol)
{
	int				ordinal;
	struct s_dylib	*ptr;

	if (macho->header->flags & MH_TWOLEVEL)
	{
		if ((ordinal = (int)GET_LIBRARY_ORDINAL(symbol->desc)))
		{
			if (ordinal == EXECUTABLE_ORDINAL)
				return (" (from executable)");
			else
			{
				ptr = get_macho_dylib_index(macho, ordinal - 1);
				if (!ptr || !ptr->name)
					return (get_nlist_library_name("bad library ordinal"));
				else
					return (get_nlist_library_name(ptr->name));
			}
		}
	}
	return ("");
}
