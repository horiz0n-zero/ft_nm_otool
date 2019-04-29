/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:57:21 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 09:08:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

inline void					swap_fatheader(struct fat_header *const fat)
{
	fat->nfat_arch = __builtin_bswap32(fat->nfat_arch);
}

inline void					swap_section32(struct section *const sec)
{
	sec->size = __builtin_bswap32(sec->size);
	sec->offset = __builtin_bswap32(sec->offset);
	sec->align = __builtin_bswap32(sec->align);
	sec->reloff = __builtin_bswap32(sec->reloff);
	sec->nreloc = __builtin_bswap32(sec->nreloc);
	sec->flags = __builtin_bswap32(sec->flags);
}

inline void					swap_section64(struct section_64 *const sec)
{
	sec->size = __builtin_bswap64(sec->size);
	sec->offset = __builtin_bswap32(sec->offset);
	sec->align = __builtin_bswap32(sec->align);
	sec->reloff = __builtin_bswap32(sec->reloff);
	sec->nreloc = __builtin_bswap32(sec->nreloc);
	sec->flags = __builtin_bswap32(sec->flags);
}

inline void					swap_sc(struct segment_command *const sc)
{
	sc->vmaddr = __builtin_bswap32(sc->vmaddr);
	sc->vmsize = __builtin_bswap32(sc->vmsize);
	sc->fileoff = __builtin_bswap32(sc->fileoff);
	sc->filesize = __builtin_bswap32(sc->filesize);
	sc->maxprot = __builtin_bswap32(sc->maxprot);
	sc->initprot = __builtin_bswap32(sc->initprot);
	sc->nsects = __builtin_bswap32(sc->nsects);
	sc->flags = __builtin_bswap32(sc->nsects);
}

inline void					swap_sc64(struct segment_command_64 *const sc)
{
	sc->vmaddr = __builtin_bswap64(sc->vmaddr);
	sc->vmsize = __builtin_bswap64(sc->vmsize);
	sc->fileoff = __builtin_bswap64(sc->fileoff);
	sc->filesize = __builtin_bswap64(sc->filesize);
	sc->maxprot = __builtin_bswap64(sc->maxprot);
	sc->initprot = __builtin_bswap64(sc->initprot);
	sc->nsects = __builtin_bswap64(sc->nsects);
	sc->flags = __builtin_bswap32(sc->nsects);
}
