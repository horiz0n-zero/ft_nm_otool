/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:02:59 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/22 16:49:52 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static inline void					nm_process_file_statics(
		struct s_nm *const nm,
		struct s_macho_binary *const bin,
		struct s_staticlib_macho *statics)
{
	while (statics)
	{
		ft_printf("\n%s(%s):\n", bin->file, statics->name);
		//sort_symbols(statics->macho->symbols, statics->macho->symbols_count,
		//		nm->sortfunc);
		if (statics->macho->is32)
			nm->print->pr_symbols_32(
					statics->macho,
					statics->macho->symbols,
					statics->macho->symbols_count);
		else
			nm->print->pr_symbols(
					statics->macho,
					statics->macho->symbols,
					statics->macho->symbols_count);
		statics = statics->next;
	}
}

void									nm_process_file(
		struct s_nm *const nm,
		struct s_macho_binary *const bin)
{
	int									index;

	index = 0;
	while (index < bin->count)
	{
		if (bin->macho[index].statics)
			nm_process_file_statics(nm, bin, bin->macho[index].statics);
		else
		{
			//sort_symbols(bin->macho[index].symbols,
			//		bin->macho[index].symbols_count, nm->sortfunc);
			if (bin->macho[index].is32)
				nm->print->pr_symbols_32(
						bin->macho + index,
						bin->macho[index].symbols,
						bin->macho[index].symbols_count);
			else
				nm->print->pr_symbols(
						bin->macho + index,
						bin->macho[index].symbols,
						bin->macho[index].symbols_count);
		}
		if (!(nm->flags & NM_A) && bin->macho[index].statics)
			break ;
		++index;
	}
}
