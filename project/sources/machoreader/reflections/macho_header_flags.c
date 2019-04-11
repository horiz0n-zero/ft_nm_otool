/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_header_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:17:13 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/11 16:10:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_reflections.h"

static const struct s_flags32_reflection	g_flags[] =
{
	{"NOUNDEFS", 0x1},
	{"INCRLINK", 0x2},
	{"DYLDLINK", 0x4},
	{"BINDATLOAD", 0x8},
	{"PREBOUND", 0x10},
	{"SPLIT_SEGS", 0x20},
	{"LAZY_INIT", 0x40},
	{"TWOLEVEL", 0x80},
	{"FORCE_FLAT", 0x100},
	{"NOMULTIDEFS", 0x200},
	{"NOFIXPREBINDING", 0x400},
	{"PREBINDABLE", 0x800},
	{"ALLMODSBOUND", 0x1000},
	{"SUBSECTIONS_VIA_SYMBOLS", 0x2000},
	{"CANONICAL", 0x4000},
	{"WEAK_DEFINES", 0x8000},
	{"BINDS_TO_WEAK", 0x10000},
	{"ALLOW_STACK_EXECUTION", 0x20000},
	{"ROOT_SAFE", 0x40000},
	{"SETUID_SAFE", 0x80000},
	{"NO_REEXPORTED_DYLIBS", 0x100000},
	{"PIE", 0x200000},
	{"DEAD_STRIPPABLE_DYLIB", 0x400000},
	{"HAS_TLV_DESCRIPTORS", 0x800000},
	{"NO_HEAP_EXECUTION", 0x1000000},
	{"APP_EXTENSION_SAFE", 0x02000000}
};

const char									*get_macho_header_flags(const uint32_t flags)
{
	static char								buffer[2048];
	char									*ptr;
	const char								*reflection;
	int										index;

	ptr = buffer;
	index = 0;
	while (index < (sizeof(g_flags) / sizeof(g_flags[0])))
	{
		if (g_flags[index].value & flags)
		{
			if (ptr != buffer)
				*ptr++ = ' ';
			reflection = g_flags[index].reflection;
			while (*reflection)
				*ptr++ = *reflection++;
		}
		index++;
	}
	*ptr = 0;
	return (buffer);
}
