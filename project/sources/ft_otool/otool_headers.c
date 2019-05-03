/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 09:35:38 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 16:48:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static const struct s_header	g_headers[] =
{
	{LC_SEGMENT, 0, print_segment},
	{LC_SEGMENT_64, 0, print_segment64},
	{LC_MAIN, 0, print_main},
	{LC_LOAD_DYLIB, 0, print_dylib},
	{LC_LOAD_WEAK_DYLIB, 0, print_dylib},
	{LC_REEXPORT_DYLIB, 0, print_dylib},
	{LC_ID_DYLIB, 0, print_dylib},
	{LC_ID_DYLINKER, 0, print_dylinker},
	{LC_LOAD_DYLINKER, 0, print_dylinker},
	{LC_DYLD_ENVIRONMENT, 0, print_dylinker},
	{LC_SYMTAB, 0, print_symtab},
	{LC_DYSYMTAB, 0, print_dysymtab},
	{LC_TWOLEVEL_HINTS, 0, print_two_level},
	{LC_UUID, 0, print_uuid},
	{LC_RPATH, 0, print_rpath},
	{LC_ROUTINES, 0, print_routines},
	{LC_ROUTINES_64, 0, print_routines64},
	{LC_FUNCTION_STARTS, 0, print_linkedit},
	{LC_DATA_IN_CODE, 0, print_linkedit},
	{LC_DYLIB_CODE_SIGN_DRS, 0, print_linkedit},
	{LC_LINKER_OPTIMIZATION_HINT, 0, print_linkedit},
	{LC_DYLD_INFO, 0, print_dyld_info},
	{LC_DYLD_INFO_ONLY, 0, print_dyld_info},
	{LC_ENCRYPTION_INFO, 0, print_encry},
	{LC_ENCRYPTION_INFO_64, 0, print_encry},
	/*{LC_BUILD_VERSION, 0, print_build_version},*/
	{LC_VERSION_MIN_MACOSX, 0, print_min_version},
	{LC_VERSION_MIN_IPHONEOS, 0, print_min_version},
	{LC_VERSION_MIN_WATCHOS, 0, print_min_version},
	{LC_VERSION_MIN_TVOS, 0, print_min_version},
	{LC_LINKER_OPTION, 0, print_linker_option},
	{LC_SYMSEG, 0, print_symseg},
	{LC_SUB_FRAMEWORK, 0, print_subframework},
	{LC_SUB_UMBRELLA, 0, print_subumbrella},
	{LC_SUB_CLIENT, 0, print_subclient},
	{LC_SUB_LIBRARY, 0, print_sublibrary},
	{LC_SOURCE_VERSION, 0, print_source_version},
	{LC_PREBIND_CKSUM, 0, print_prebind},
	{LC_CODE_SIGNATURE, 0, print_linkedit},
	{LC_SEGMENT_SPLIT_INFO, 0, print_linkedit},
	{LC_PREBOUND_DYLIB, 0, print_prebound},
	{LC_IDFVMLIB, 0, print_fvmlib},
	{LC_LOADFVMLIB, 0, print_fvmlib},
	{LC_FVMFILE, 0, print_fvmfile_command},
	{LC_NOTE, 0, print_note}
};

void							otool_headers(
		struct s_otool *const otool,
		struct s_macho *const macho)
{
	int							index;
	int							i;
	struct s_loadcommand		*lc;

	index = 0;
	while (index < macho->loadcommands_count)
	{
		lc = macho->loadcommands + index;
		ft_printf("Load command %d\n", index++);
		ft_printf("                   cmd %s\n", lc->type);
		ft_printf("               cmdsize %zd\n", lc->size);
		i = 0;
		while (i < (sizeof(g_headers) / sizeof(g_headers[0])))
		{
			if (g_headers[i].cmd == lc->cmdtype)
			{
				g_headers[i].print(lc);
				break ;
			}
			i++;
		}
	}
}
