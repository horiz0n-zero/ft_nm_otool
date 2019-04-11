/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 09:18:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/11 13:35:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_reflections.h"

static const struct s_cputype_reflection	g_cputypes[] =
{
	{CPU_TYPE_ANY, "ANY"},
	{CPU_TYPE_VAX, "VAX"},
	{CPU_TYPE_MC680x0, "MC680x0"},
	{CPU_TYPE_X86, "X86"},
	{CPU_TYPE_I386, "I386"},
	{CPU_TYPE_X86_64, "X86_64"},
	{CPU_TYPE_MC98000, "MC98000"},
	{CPU_TYPE_HPPA, "HPPA"},
	{CPU_TYPE_ARM, "ARM"},
	{CPU_TYPE_ARM64, "ARM64"},
	{CPU_TYPE_MC88000, "MC88000"},
	{CPU_TYPE_SPARC, "SPARC"},
	{CPU_TYPE_I860, "I860"},
	{CPU_TYPE_POWERPC, "POWERPC"},
	{CPU_TYPE_POWERPC64, "POWERPC64"}
};

static const struct s_cpusubtype_reflection	g_cpusubtypes[] =
{
	{
		CPU_TYPE_X86_64,
		{
			{CPU_SUBTYPE_X86_64_ALL, "ALL"},
			{CPU_SUBTYPE_X86_64_ALL, "ALL"}
		}
	}
};

const char									*get_cputype(const cpu_type_t cputype)
{
	int										index;

	index = 0;
	while (index < (sizeof(g_cputypes) / sizeof(g_cputypes[0])))
	{
		if (g_cputypes[index].value == cputype)
			return (g_cputypes[index].reflection);
		index++;
	}
	return ("???");
}

const char									*get_cpusubtype(const cpu_type_t type, const cpu_subtype_t cputype)
{
	return ("???");
}
