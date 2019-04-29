/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:21:01 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 09:32:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void							macho_read_segment(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const loadc, const uint32_t type)
{
	void *const						position = binary->position;

	if (type == LC_SEGMENT_64 || type == LC_SEGMENT)
	{
		loadc->segment = ft_memalloc(sizeof(struct s_segment));
		if (macho->is32)
		{
			loadc->segment->name = ((struct segment_command*)loadc->content)->segname;
			if (macho->isswap)
				swap_sc(loadc->content);
			loadc->segment->count = (int)((struct segment_command*)loadc->content)->nsects;
		}
		else
		{
			loadc->segment->name = ((struct segment_command_64*)loadc->content)->segname;
			if (macho->isswap)
				swap_sc64(loadc->content);
			loadc->segment->count = (int)((struct segment_command_64*)loadc->content)->nsects;
		}
		if (loadc->segment->count)
			read_macho_segment_sections(binary, macho, loadc);
		binary->position = position;
	}
	if (type == LC_LOAD_DYLIB || type == LC_LOAD_WEAK_DYLIB || type == LC_LAZY_LOAD_DYLIB || type == LC_REEXPORT_DYLIB)
		get_macho_dylib(binary, macho, loadc);
}

static void							macho_read_lc(struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	struct load_command				*lc;
	struct s_loadcommand			*loadc;
	int								index;

	index = 0;
	macho->loadcommands_count = (int)macho->header->ncmds;
	macho->loadcommands = ft_memalloc(sizeof(struct s_loadcommand) * (size_t)macho->header->ncmds);
	while (index < macho->loadcommands_count)
	{
		if (!(lc = get_object(binary, binary->position, sizeof(struct load_command))))
			return (set_error(binary, MRERR_MACHO));
		loadc = macho->loadcommands + index++;
		if (macho->isswap)
			swap_lc(lc);
		if (!(loadc->type = get_lc(lc->cmd)))
			return (set_error(binary, MRERR_MACHO));
		if (!(loadc->content = getset_object(binary, &binary->position, lc->cmdsize)))
			return (set_error(binary, MRERR_MACHO));
		loadc->size = (size_t)lc->cmdsize;
		loadc->cmdtype = lc->cmd;
		macho_read_segment(binary, macho, loadc, lc->cmd);
		if (binary->error)
			return ;
	}
	set_macho_sections(binary, macho);
	read_macho_symtab(binary, macho);
}

static inline void					try_read_macho_static_library(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	if (!ft_strncmp(binary->position, ARMAG, SARMAG))
	{
		set_object(binary, sizeof(SARMAG));
		read_static_lib(binary, macho);
	}
	else
		binary->error = MRERR_MACHO;
}

void								read_macho_header(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	macho->header = get_object(binary, binary->position, sizeof(struct mach_header));
	if (!macho->header)
		return (set_error(binary, MRERR_MACHO));
	if (macho->header->magic == MH_MAGIC ||
			macho->header->magic == MH_CIGAM)
	{
		macho->is32 = 1;
		if ((macho->isswap = (macho->header->magic == MH_CIGAM) ? 1 : 0))
			swap_mach32(binary->position);
		set_object(binary, sizeof(struct mach_header));
		macho_read_lc(binary, macho);
	}
	else if (macho->header->magic == MH_MAGIC_64 ||
			macho->header->magic == MH_CIGAM_64)
	{
		macho->is32 = 0;
		if ((macho->isswap = (macho->header->magic == MH_CIGAM_64) ? 1 : 0))
			swap_mach64(binary->position);
		set_object(binary, sizeof(struct mach_header_64));
		macho_read_lc(binary, macho);
	}
	else
		try_read_macho_static_library(binary, macho);
}
