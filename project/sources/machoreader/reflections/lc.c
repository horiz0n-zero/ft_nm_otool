/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:55:12 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/11 16:34:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_reflections.h"

static const char				*g_lc[] =
{
	"LC_SEGMENT",
	"LC_SYMTAB",
	"LC_SYMSEG",
	"LC_THREAD",
	"LC_UNIXTHREAD",
	"LC_LOADFVMLIB",
	"LC_IDFVMLIB",
	"LC_IDENT",
	"LC_FVMFILE",
	"LC_PREPAGE",
	"LC_DYSYMTAB",
	"LC_LOAD_DYLIB",
	"LC_ID_DYLIB",
	"LC_LOAD_DYLINKER",
	"LC_ID_DYLINKER",
	"LC_PREBOUND_DYLIB",
	"LC_ROUTINES",
	"LC_SUB_FRAMEWORK",
	"LC_SUB_UMBRELLA",
	"LC_SUB_CLIENT",
	"LC_SUB_LIBRARY",
	"LC_TWOLEVEL_HINTS",
	"LC_PREBIND_CKSUM",
	"LC_LOAD_WEAK_DYLIB",
	"LC_SEGMENT_64",
	"LC_ROUTINES_64",
	"LC_UUID",
	"LC_RPATH",
	"LC_CODE_SIGNATURE",
	"LC_SEGMENT_SPLIT_INFO",
	"LC_REEXPORT_DYLIB",
	"LC_LAZY_LOAD_DYLIB",
	"LC_ENCRYPTION_INFO",
	"LC_DYLD_INFO",
	"LC_DYLD_INFO_ONLY",
	"LC_LOAD_UPWARD_DYLIB",
	"LC_VERSION_MIN_MACOSX",
	"LC_VERSION_MIN_IPHONEOS",
	"LC_FUNCTION_STARTS",
	"LC_DYLD_ENVIRONMENT"
};

const char						*get_lc(const uint32_t cmd)
{
	printf("#%d\n", (cmd & ~LC_REQ_DYLD) >= (sizeof(g_lc) / sizeof(g_lc[0])));
	if ((cmd & ~LC_REQ_DYLD) >= (sizeof(g_lc) / sizeof(g_lc[0])))
		return (NULL);
	return (g_lc[cmd & ~LC_REQ_DYLD]);
}
