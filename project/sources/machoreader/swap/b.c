/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:09:00 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 09:43:15 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

inline void			swap_mach32(
		struct mach_header *const header)
{
	header->cputype = __builtin_bswap32(header->cputype);
	header->cpusubtype = __builtin_bswap32(header->cpusubtype);
	header->filetype = __builtin_bswap32(header->filetype);
	header->ncmds = __builtin_bswap32(header->ncmds);
	header->sizeofcmds = __builtin_bswap32(header->sizeofcmds);
	header->flags = __builtin_bswap32(header->flags);
}

inline void			swap_mach64(
		struct mach_header_64 *const header)
{
	header->cputype = __builtin_bswap32(header->cputype);
	header->cpusubtype = __builtin_bswap32(header->cpusubtype);
	header->filetype = __builtin_bswap32(header->filetype);
	header->ncmds = __builtin_bswap32(header->ncmds);
	header->sizeofcmds = __builtin_bswap32(header->sizeofcmds);
	header->flags = __builtin_bswap32(header->flags);
	header->flags = __builtin_bswap32(header->reserved);
}

inline void			swap_lc(
		struct load_command *const lc)
{
	lc->cmd = __builtin_bswap32(lc->cmd);
	lc->cmdsize = __builtin_bswap32(lc->cmdsize);
}

inline void			swap_fatarch32(
		struct fat_arch *const arch)
{
	arch->cputype = __builtin_bswap32(arch->cputype);
	arch->cpusubtype = __builtin_bswap32(arch->cpusubtype);
	arch->offset = __builtin_bswap32(arch->offset);
	arch->size = __builtin_bswap32(arch->size);
	arch->align = __builtin_bswap32(arch->align);
}

inline void			swap_fatarch64(
		struct fat_arch_64 *const arch)
{
	arch->cputype = __builtin_bswap32(arch->cputype);
	arch->cpusubtype = __builtin_bswap32(arch->cpusubtype);
	arch->offset = __builtin_bswap64(arch->offset);
	arch->size = __builtin_bswap64(arch->size);
	arch->align = __builtin_bswap32(arch->align);
}
