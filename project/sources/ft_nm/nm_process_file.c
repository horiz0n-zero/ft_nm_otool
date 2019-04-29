/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:02:59 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 12:53:39 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void								nm_process_skipable(
		struct s_nm *const nm,
		struct s_macho *const macho)
{
	struct s_symbol					*symbol;
	int								count;

	count = macho->symbols_count;
	symbol = macho->symbols;
	while (count--)
	{
		if (((symbol->type & N_STAB) && !(nm->flags & NM_D)) ||
				((nm->flags & NM_U) && symbol->value) ||
				((nm->flags & NM_G) && !(symbol->type & N_EXT)))
			symbol->skip = 1;
		symbol++;
	}
}

static inline void					nm_process_file_statics(
		struct s_nm *const nm,
		struct s_macho_binary *const bin,
		struct s_staticlib_macho *statics)
{
	while (statics)
	{
		ft_printf("\n%s(%s):\n", bin->file, statics->name);
		nm_process_skipable(nm, statics->macho);
		sort_symbols(statics->macho->symbols, statics->macho->symbols_count, nm->flags & NM_R, nm->sortfunc);
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
	struct s_macho						*ptr;
	int									select;

	if (nm->flags & NM_A && !(select = 0))
		index = 0;
	else
		index = select_arch(bin, &select);
	while (index < bin->count)
	{
		ptr = bin->macho + index;
		if (bin->count > 1 && !ptr->statics && !select)
			ft_printf("\n%s (for architecture %s):\n", bin->file, get_cputype(ptr->header->cputype, 1));
		if (ptr->statics)
			nm_process_file_statics(nm, bin, ptr->statics);
		else
		{
			nm_process_skipable(nm, ptr);
			sort_symbols(ptr->symbols, ptr->symbols_count, nm->flags & NM_R, nm->sortfunc);
			if (ptr->is32)
				nm->print->pr_symbols_32(ptr, ptr->symbols, ptr->symbols_count);
			else
				nm->print->pr_symbols(ptr, ptr->symbols, ptr->symbols_count);
		}
		if (select)
			break ;
		++index;
	}
}
