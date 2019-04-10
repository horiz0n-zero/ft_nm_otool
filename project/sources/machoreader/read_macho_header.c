/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:21:01 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 14:31:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

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
	}
	else if (macho->header->magic == MH_MAGIC_64 ||
			macho->header->magic == MH_CIGAM_64)
	{
		macho->is32 = 0;
		if ((macho->isswap = (macho->header->magic == MH_CIGAM_64) ? 1 : 0))
			mem_swap64(binary->position, sizeof(struct mach_header_64));
		SETO(binary, sizeof(struct mach_header_64));
	}
	else
	{
		binary->error = "bad macho";
	}
}
