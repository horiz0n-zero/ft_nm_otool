/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:21:01 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/12 15:57:52 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void							macho_read_segment(struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const loadc, const uint32_t type)
{
	if (type == LC_SEGMENT_64 || type == LC_SEGMENT)
	{
		loadc->segments = ft_memalloc(sizeof(struct s_segment));
		if (macho->is32)
			loadc->segments->name = AS(loadc->content, struct segment_command)->segname;
		else
			loadc->segments->name = AS(loadc->content, struct segment_command_64)->segname;
	}
	else
		loadc->segments = NULL;
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
		if (!(lc = GETO(binary, binary->position, struct load_command)))
			return (set_error(binary, "< load_command"));
		loadc = macho->loadcommands + index++;
		if (macho->isswap)
			macho->is32 ? MSWAP32(lc, struct load_command) : MSWAP64(lc, struct load_command);
		if (!(loadc->type = get_lc(lc->cmd)))
			return (set_error(binary, "bad load command"));
		if (!(loadc->content = GETSET(binary, &binary->position, lc->cmdsize)))
			return (set_error(binary, "bad load command content"));
		loadc->size = (size_t)lc->cmdsize;
		macho_read_segment(binary, macho, loadc, lc->cmd);
		if (binary->error)
			return ;
	}
}

static inline void					try_read_macho_static_library(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	static const uint64_t			magic = 0xA3E686372613C21;

	if (!ft_strncmp(binary->position, ARMAG, SARMAG))
	{
		SETO(binary, SARMAG);
		read_static_lib(binary, macho);
	}
	else
		binary->error = "bad macho";
}

void								read_macho_header(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	macho->header = GETO(binary, binary->position, struct mach_header);
	if (!macho->header)
		return (set_error(binary, "size macho <"));
	if (macho->header->magic == MH_MAGIC ||
			macho->header->magic == MH_CIGAM)
	{
		macho->is32 = 1;
		if ((macho->isswap = (macho->header->magic == MH_CIGAM) ? 1 : 0))
			MSWAP32(binary->position, struct mach_header);
		SETO(binary, struct mach_header);
		macho_read_lc(binary, macho);
	}
	else if (macho->header->magic == MH_MAGIC_64 ||
			macho->header->magic == MH_CIGAM_64)
	{
		macho->is32 = 0;
		if ((macho->isswap = (macho->header->magic == MH_CIGAM_64) ? 1 : 0))
			MSWAP64(binary->position, struct mach_header_64);
		SETO(binary, struct mach_header_64);
		macho_read_lc(binary, macho);
	}
	else
		try_read_macho_static_library(binary, macho);
}
