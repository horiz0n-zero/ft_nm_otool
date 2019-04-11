/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:21:01 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/11 16:27:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void							macho_read_lc(struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	struct load_command				*lc;
	int								index;

	index = 0;
	macho->loadcommands_count = (int)macho->header->ncmds;
	macho->loadcommands = malloc(sizeof(struct s_loadcommand) * (size_t)macho->header->ncmds);
	while (index < macho->loadcommands_count)
	{
		if (!(lc = GETSETO(binary, &binary->position, struct load_command)))
			return (set_error(binary, "< load_command"));
		if (!(macho->loadcommands[index].type = get_lc(lc->cmd)))
			return (set_error(binary, "bad load command"));
		if (!(macho->loadcommands[index].content = GETSET(binary, &binary->position, lc->cmdsize)))
			return (set_error(binary, "bad load command content"));
		index++;
	}
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
			mem_swap32(binary->position, sizeof(struct mach_header));
		SETO(binary, sizeof(struct mach_header));
		macho_read_lc(binary, macho);
	}
	else if (macho->header->magic == MH_MAGIC_64 ||
			macho->header->magic == MH_CIGAM_64)
	{
		macho->is32 = 0;
		if ((macho->isswap = (macho->header->magic == MH_CIGAM_64) ? 1 : 0))
			mem_swap64(binary->position, sizeof(struct mach_header_64));
		SETO(binary, sizeof(struct mach_header_64));
		macho_read_lc(binary, macho);
	}
	else
	{
		binary->error = "bad macho";
	}
}
