/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_symtab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:40:56 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/19 15:06:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static inline void			fill_symbol32(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct nlist *const list,
		struct s_symbol *const symbol)
{
	if (list->n_sect != NO_SECT)
	{
		if (!macho->sections || (int)list->n_sect > macho->sections_count)
			return (set_error(binary, "n_sect to to bad for sure!"));
		symbol->section = macho->sections[(int)list->n_sect - 1];
	}
}

static void					symtab_loop32(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct symtab_command *const symtab)
{
	struct nlist			*list;
	typeof(symtab->nsyms)	index;
	char *const				strtab = (((char*)macho->header) + symtab->stroff);

	if (!get_object(binary, macho->header, (size_t)symtab->symoff + symtab->nsyms * sizeof(struct nlist)))
		return (set_error(binary, "insuff symtab size32"));
	if (!get_object(binary, macho->header, (size_t)symtab->stroff + symtab->strsize))
		return (set_error(binary, "insuff symtab str size32"));
	macho->symbols = ft_memalloc(sizeof(struct s_symbol) * (size_t)symtab->nsyms);
	macho->symbols_count = (int)symtab->nsyms;
	list = (void*)(((char*)macho->header) + symtab->symoff);
	index = 0;
	while (index < symtab->nsyms)
	{
		fill_symbol32(binary, macho, list, macho->symbols + index);
		macho->symbols[index++].name = strtab + list->n_un.n_strx;
		list++;
	}
}

static inline void			fill_symbol64(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct nlist_64 *const list,
		struct s_symbol *const symbol)
{
	if (list->n_sect != NO_SECT) // -1
	{
		if (!macho->sections || (int)list->n_sect > macho->sections_count)
			return (set_error(binary, "n_sect to to bad for sure !"));
		symbol->section = macho->sections[(int)list->n_sect - 1];
	}
}

static void					symtab_loop64(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct symtab_command *const symtab)
{
	struct nlist_64			*list;
	typeof(symtab->nsyms)	index;
	char *const				strtab = (((char*)macho->header) + symtab->stroff);

	if (!get_object(binary, macho->header, (size_t)symtab->symoff + symtab->nsyms * sizeof(struct nlist_64)))
		return (set_error(binary, "insuff symtab size64"));
	if (!get_object(binary, macho->header, (size_t)symtab->stroff + symtab->strsize))
		return (set_error(binary, "insuff symtab str size64"));
	macho->symbols = ft_memalloc(sizeof(struct s_symbol) * (size_t)symtab->nsyms);
	macho->symbols_count = (int)symtab->nsyms;
	list = (void*)(((char*)macho->header) + symtab->symoff);
	index = 0;
	while (index < symtab->nsyms)
	{
		fill_symbol64(binary, macho, list, macho->symbols + index);
		macho->symbols[index++].name = strtab + list->n_un.n_strx;
		list++;
	}
}

void						read_macho_symtab(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	struct s_loadcommand	*cmd;
	struct symtab_command	*symtab;

	if (!(cmd = get_macho_first_loadcommand(macho, LC_SYMTAB)))
		return (set_error(binary, "no symtab found in mach-object"));
	if (cmd->size != sizeof(struct symtab_command))
		return (set_error(binary, "bad symtab_command size"));
	symtab = cmd->content;
	if (macho->isswap)
	{
		symtab->symoff = __builtin_bswap32(symtab->symoff);
		symtab->nsyms = __builtin_bswap32(symtab->nsyms);
		symtab->stroff = __builtin_bswap32(symtab->stroff);
		symtab->strsize = __builtin_bswap32(symtab->strsize);
	}
	if (macho->is32)
		symtab_loop32(binary, macho, symtab);
	else
		symtab_loop64(binary, macho, symtab);
}
