/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_print_o.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:47:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/26 13:32:00 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void						nm_print_object_only(
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	char *const					f = !macho->is32 ?
		"%s: %016x %c %s\n" :
		"%s: %08x %c %s\n";
	char *const					uf = !macho->is32 ?
		"%s:                  %c %s\n" :
		"%s:          %c %s\n";
	struct s_symbol				*symbol;
	struct s_symbol *const		e = macho->symbols + macho->symbols_count;

	symbol = macho->symbols;
	while (symbol < e)
	{
		if (!symbol->skip)
		{
			if (symbol->value)
				ft_printf(f, bin->file, symbol->value, get_nlist_extchar(symbol), symbol->name);
			else
				ft_printf(uf, bin->file, get_nlist_extchar(symbol), symbol->name);
		}
		symbol++;
	}
}

static void						nm_print_object_multi(
		struct s_macho_binary *const bin,
		struct s_macho *const macho, const char *const arch)
{
	char *const					f = !macho->is32 ?
		"(for architecture %s):%s: %016x %c %s\n" :
		"(for architecture %s):%s: %08x %c %s\n";
	char *const					uf = !macho->is32 ?
		"(for architecture %s):%s:                  %c %s\n" :
		"(for architecture %s):%s:          %c %s\n";
	struct s_symbol				*symbol;
	struct s_symbol *const		e = macho->symbols + macho->symbols_count;

	symbol = macho->symbols;
	while (symbol < e)
	{
		if (!symbol->skip)
		{
			if (symbol->value)
				ft_printf(f, arch, bin->file, symbol->value, get_nlist_extchar(symbol), symbol->name);
			else
				ft_printf(uf, arch, bin->file, get_nlist_extchar(symbol), symbol->name);
		}
		symbol++;
	}
}

static void						nm_print_object_statics(
		struct s_macho_binary *const bin,
		struct s_staticlib_macho *const statics,
		struct s_macho *const macho)
{
	char *const					f = !macho->is32 ? "%s:%s: %016x %c %s\n" : "%s:%s: %08x %c %s\n";
	char *const					uf = !macho->is32 ? "%s:%s:          %c %s\n" : "%s:%s:                  %c %s\n";
	struct s_symbol				*symbol;
	struct s_symbol *const		e = macho->symbols + macho->symbols_count;

	symbol = macho->symbols;
	while (symbol < e)
	{
		if (!symbol->skip)
		{
			if (symbol->value)
				ft_printf(f, bin->file, statics->name, symbol->value, get_nlist_extchar(symbol), symbol->name);
			else
				ft_printf(uf, bin->file, statics->name, get_nlist_extchar(symbol), symbol->name);
		}
		symbol++;
	}
}

static void						nm_print_object(
		struct s_nm *const nm,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		const int multi)
{
	struct s_staticlib_macho	*statics;

	if (macho->statics)
	{
		statics = macho->statics;
		while (statics)
		{
			nm_process_skipable(nm, statics->macho);
			sort_symbols(statics->macho->symbols, statics->macho->symbols_count, nm->flags & NM_R, nm->sortfunc);
			nm_print_object_statics(bin, statics, statics->macho);
			statics = statics->next;
		}
		return ;
	}
	nm_process_skipable(nm, macho);
	sort_symbols(macho->symbols, macho->symbols_count, nm->flags & NM_R, nm->sortfunc);
	if (multi)
		nm_print_object_multi(bin, macho, get_cputype(macho->header->cputype, 1));
	else
		nm_print_object_only(bin, macho);
}

void							nm_print_o(
		struct s_nm *const nm,
		char **argv)
{
	static char					*default_argv[] = {"a.out", NULL};
	struct s_macho_binary		*bin;
	int							index;

	if (!*argv)
		argv = default_argv;
	while (*argv)
	{
		bin = get_macho_binary(*argv++);
		if (bin->error)
			ft_fprintf(STDERR_FILENO, "ft_nm: %s: %s.\n", bin->file, bin->error);
		else
		{
			index = 0;
			while (index < bin->count)
			{
				nm_print_object(nm, bin, bin->macho + index, bin->count > 1);
				++index;
			}
		}
		unget_macho_binary(bin);
	}
}
