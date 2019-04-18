/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lc_a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:31:00 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/18 13:51:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

struct symtab_command				*get_lc_symtab(
		struct s_macho *const macho,
		struct symtab_command *const in)
{
	if (macho->isswap)
	{
		in->symoff = __builtin_bswap32(in->symoff);
		in->nsyms = __builtin_bswap32(in->nsyms);
		in->stroff = __builtin_bswap32(in->stroff);
		in->strsize = __builtin_bswap32(in->strsize);
	}
	return (in);
}
