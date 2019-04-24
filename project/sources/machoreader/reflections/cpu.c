/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 09:18:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/24 11:25:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_reflections.h"

static const struct s_cputype_reflection	g_cputypes[] =
{
	{CPU_TYPE_ANY, "ANY", "all"},
	{CPU_TYPE_VAX, "VAX", "vax"},
	{CPU_TYPE_MC680x0, "MC680x0", "mc680"},
	{CPU_TYPE_X86, "X86", "x86"},
	{CPU_TYPE_I386, "I386", "i386"},
	{CPU_TYPE_X86_64, "X86_64", "x86-64"},
	{CPU_TYPE_MC98000, "MC98000", "mc98000"},
	{CPU_TYPE_HPPA, "HPPA", "hppa"},
	{CPU_TYPE_ARM, "ARM", "arm"},
	{CPU_TYPE_ARM64, "ARM64", "arm64"},
	{CPU_TYPE_MC88000, "MC88000", "mc88000"},
	{CPU_TYPE_SPARC, "SPARC", "sparc"},
	{CPU_TYPE_I860, "I860", "i860"},
	{CPU_TYPE_POWERPC, "POWERPC", "ppc"},
	{CPU_TYPE_POWERPC64, "POWERPC64", "ppc64"}
};

static const struct	s_cpusubtype_in			g_cpusubtypes_array[] =
{
	{CPU_SUBTYPE_MULTIPLE, "MULTIPLE"},
	{CPU_SUBTYPE_LITTLE_ENDIAN, "LITTLE_ENDIAN"},
	{CPU_SUBTYPE_BIG_ENDIAN, "BIG_ENDIAN"},
	{CPU_SUBTYPE_VAX_ALL,  "ALL"},
	{CPU_SUBTYPE_VAX780,  "780"},
	{CPU_SUBTYPE_VAX785,  "785"},
	{CPU_SUBTYPE_VAX750,  "750"},
	{CPU_SUBTYPE_VAX730,  "730"},
	{CPU_SUBTYPE_UVAXI,  "I"},
	{CPU_SUBTYPE_UVAXII,  "II"},
	{CPU_SUBTYPE_VAX8200,  "8200"},
	{CPU_SUBTYPE_VAX8500,  "8500"},
	{CPU_SUBTYPE_VAX8600,  "8600"},
	{CPU_SUBTYPE_VAX8650,  "8650"},
	{CPU_SUBTYPE_VAX8800,  "8800"},
	{CPU_SUBTYPE_UVAXIII,  "III"},
	{CPU_SUBTYPE_MC680x0_ALL, "ALL"},
	{CPU_SUBTYPE_MC68030, "30"},
	{CPU_SUBTYPE_MC68040, "40"},
	{CPU_SUBTYPE_MC68030_ONLY, "30_ONLY"},
	{CPU_SUBTYPE_I386_ALL, "ALL"},
	{CPU_SUBTYPE_386, "386"},
	{CPU_SUBTYPE_486, "486"},
	{CPU_SUBTYPE_486SX, "486SX"},
	{CPU_SUBTYPE_586, "586"},
	{CPU_SUBTYPE_PENT, "PENT"},
	{CPU_SUBTYPE_PENTPRO, "PENTPRO"},
	{CPU_SUBTYPE_PENTII_M3, "PENTII_M3"},
	{CPU_SUBTYPE_PENTII_M5, "PENTII_M5"},
	{CPU_SUBTYPE_CELERON, "CELERON"},
	{CPU_SUBTYPE_CELERON_MOBILE, "CELERON_MOBILE"},
	{CPU_SUBTYPE_PENTIUM_3, "PENTIUM_3"},
	{CPU_SUBTYPE_PENTIUM_3_M, "PENTIUM_3_M"},
	{CPU_SUBTYPE_PENTIUM_3_XEON, "PENTIUM_3_XEON"},
	{CPU_SUBTYPE_PENTIUM_M, "PENTIUM_M"},
	{CPU_SUBTYPE_PENTIUM_4, "PENTIUM_4"},
	{CPU_SUBTYPE_PENTIUM_4_M, "PENTIUM_4_M"},
	{CPU_SUBTYPE_ITANIUM, "ITANIUM"},
	{CPU_SUBTYPE_ITANIUM_2, "ITANIUM_2"},
	{CPU_SUBTYPE_XEON, "XEON"},
	{CPU_SUBTYPE_XEON_MP, "XEON_MP"},
	{CPU_SUBTYPE_X86_ALL, "ALL"},
	{CPU_SUBTYPE_X86_64_ALL, "64_ALL"},
	{CPU_SUBTYPE_X86_ARCH1, "ARCH1"},
	{CPU_SUBTYPE_X86_64_H, "64_H"},
	{CPU_SUBTYPE_HPPA_ALL, "ALL"},
	{CPU_SUBTYPE_HPPA_7100, "7100"},
	{CPU_SUBTYPE_HPPA_7100LC, "7100LC"},
	{CPU_SUBTYPE_MC88000_ALL, "ALL"},
	{CPU_SUBTYPE_MC88100, "MC88100"},
	{CPU_SUBTYPE_MC88110, "MC88110"},
	{CPU_SUBTYPE_SPARC_ALL, "ALL"},
	{CPU_SUBTYPE_POWERPC_ALL, "ALL"},
	{CPU_SUBTYPE_POWERPC_601, "601"},
	{CPU_SUBTYPE_POWERPC_602, "602"},
	{CPU_SUBTYPE_POWERPC_603, "603"},
	{CPU_SUBTYPE_POWERPC_603e, "603e"},
	{CPU_SUBTYPE_POWERPC_603ev, "603ev"},
	{CPU_SUBTYPE_POWERPC_604, "604"},
	{CPU_SUBTYPE_POWERPC_604e, "604e"},
	{CPU_SUBTYPE_POWERPC_620, "620"},
	{CPU_SUBTYPE_POWERPC_750, "750"},
	{CPU_SUBTYPE_POWERPC_7400, "7400"},
	{CPU_SUBTYPE_POWERPC_7450, "7450"},
	{CPU_SUBTYPE_POWERPC_970, "970"},
	{CPU_SUBTYPE_ARM_ALL, "ALL"},
	{CPU_SUBTYPE_ARM_V4T, "V4T"},
	{CPU_SUBTYPE_ARM_V6, "V6"},
	{CPU_SUBTYPE_ARM_V5TEJ, "V5TEJ"},
	{CPU_SUBTYPE_ARM_XSCALE, "XSCALE"},
	{CPU_SUBTYPE_ARM_V7, "V7"},
	{CPU_SUBTYPE_ARM_V7F, "V7F"},
	{CPU_SUBTYPE_ARM_V7S, "V7S"},
	{CPU_SUBTYPE_ARM_V7K, "V7K"},
	{CPU_SUBTYPE_ARM_V6M, "V6M"},
	{CPU_SUBTYPE_ARM_V7M, "V7M"},
	{CPU_SUBTYPE_ARM_V7EM, "V7EM"},
	{CPU_SUBTYPE_ARM_V8, "V8"},
	{CPU_SUBTYPE_ARM_ALL, "ALL"},
	{CPU_SUBTYPE_ARM_V4T, "V4T"},
	{CPU_SUBTYPE_ARM_V6, "V6"},
	{CPU_SUBTYPE_ARM_V5TEJ, "V5TEJ"},
	{CPU_SUBTYPE_ARM_XSCALE, "XSCALE"},
	{CPU_SUBTYPE_ARM_V7, "V7"},
	{CPU_SUBTYPE_ARM_V7F, "V7F"},
	{CPU_SUBTYPE_ARM_V7S, "V7S"},
	{CPU_SUBTYPE_ARM_V7K, "V7K"},
	{CPU_SUBTYPE_ARM_V6M, "V6M"},
	{CPU_SUBTYPE_ARM_V7M, "V7M"},
	{CPU_SUBTYPE_ARM_V7EM, "V7EM"},
	{CPU_SUBTYPE_ARM_V8, "V8"},
	{CPU_SUBTYPE_ARM64_ALL, "ALL"},
	{CPU_SUBTYPE_ARM64_V8, "v8"},
	{CPU_SUBTYPE_I860_ALL, "ALL"},
	{CPU_SUBTYPE_I860_860, "860"}
};

static const struct	s_cpusubtype_reflection	g_cpusubtypes[] =
{
	{CPU_TYPE_ANY, 0, 3},
	{CPU_TYPE_VAX, 3, 13},
	{CPU_TYPE_MC680x0, 17, 4},
	{CPU_TYPE_X86, 42, 4},
	{CPU_TYPE_X86_64, 42, 4},
	{CPU_TYPE_I386, 21, 21},
	{CPU_TYPE_MC98000, 48, 3},
	{CPU_TYPE_HPPA, 46, 3},
	{CPU_TYPE_MC88000, 48, 3},
	{CPU_TYPE_SPARC, 51, 1},
	{CPU_TYPE_POWERPC, 52, 13},
	{CPU_TYPE_ARM, 78, 13},
	{CPU_TYPE_ARM64, 91, 2},
	{CPU_TYPE_I860, 93, 2}
};

const char									*get_cputype(
		const cpu_type_t cputype,
		const int small)
{
	int										index;

	index = 0;
	while (index < (sizeof(g_cputypes) / sizeof(g_cputypes[0])))
	{
		if (g_cputypes[index].value == cputype)
		{
			if (small)
				return (g_cputypes[index].reflection_small);
			else
				return (g_cputypes[index].reflection);
		}
		index++;
	}
	return ("???");
}

const char									*get_cpusubtype(const cpu_type_t type, const cpu_subtype_t cputype)
{
	int										index;
	int										count;
	int										i;

	index = 0;
	while (index < (sizeof(g_cpusubtypes) / sizeof(g_cpusubtypes[0])))
	{
		if (g_cpusubtypes[index].value == type)
		{
			count = g_cpusubtypes[index].count;
			index = g_cpusubtypes[index].index;
			i = 0;
			while (i < count)
			{
				if (g_cpusubtypes_array[i + index].value == cputype)
					return (g_cpusubtypes_array[i + index].reflection);
				i++;
			}
			break ;
		}
		++index;
	}
	return ("ALL");
}
