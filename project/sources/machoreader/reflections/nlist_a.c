/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:32:16 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/22 16:43:10 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

/*
**		(symbols[i].nl.n_type & N_TYPE) == N_UNDF &&
**		symbols[i].nl.n_value == 0) ||
**		(symbols[i].nl.n_type & N_TYPE) == N_PBUD)
*/

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
					return (get_nlist_library_name(" (from bad library ordinal)"));
				else
					return (get_nlist_library_name(ptr->name));
			}
		}
	}
	return ("");
}
