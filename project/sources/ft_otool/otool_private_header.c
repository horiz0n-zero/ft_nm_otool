/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_private_header.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 08:53:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 09:34:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void					otool_private_header(
		struct s_otool *const otool,
		struct s_macho *const macho)
{
	write(STDOUT_FILENO, "Mach header\n", sizeof("Mach header\n"));
	if (otool->flags & OTOOL_M)
	{
		ft_printf("      magic cputype cpusubtype  caps   filetype ncmds sizeofcmds  flags\n");
		ft_printf("%s%8s%11s  0x%x %11s %-5d %-10d  %s\n",
			get_magic(macho->header->magic),
			get_cputype(macho->header->cputype, 0),
			get_cpusubtype(macho->header->cputype, macho->header->cpusubtype),
			0,
			get_macho_filetype(macho->header->filetype),
			macho->header->ncmds, macho->header->sizeofcmds,
			get_macho_header_flags(macho->header->flags));
	}
	else
	{
		ft_printf("      magic cputype   cpusubtype  caps filetype ncmds sizeofcmds flags\n");
		ft_printf(" %#x %-8d  %-10d  0x%#02x %8d %5d %10d 0x%08x\n",
				macho->header->magic, macho->header->cputype,
				macho->header->cpusubtype, 0,
				macho->header->filetype,
				macho->header->ncmds, macho->header->sizeofcmds,
				macho->header->flags);
	}
}
