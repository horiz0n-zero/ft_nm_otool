/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_content_default.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:57:36 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 16:57:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static const char				*g_printf_rip64[] =
{
	"",
	"%016llx\t%02hhx\n"
	"%016llx\t%02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%016llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
};

static const char				*g_printf_rip32[] =
{
	"",
	"%08llx\t%02hhx\n"
	"%08llx\t%02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
	"%08llx\t%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n",
};

void							otool_content_default_64(
		struct s_otool *const otool,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_section *const section)
{
	struct section_64 *const	rawsection = (void*)section->sectname;
	uint64_t					addr;
	size_t						req;
	char						*str;

	addr = rawsection->addr;
	str = section->content;
	req = section->content_size;
	while (req > 16)
	{
		ft_printf(g_printf_rip64[15], addr, str[0], str[1], str[2], str[3], str[4],
				str[5], str[6], str[7], str[8], str[9], str[10],
				str[11], str[12], str[13], str[14], str[15]);
		str += 16;
		addr += 16;
		req -= 16;
	}
	if (req <= 0)
		return ;
	ft_printf(g_printf_rip64[req - 1], addr, str[0], str[1], str[2], str[3], str[4],
			str[5], str[6], str[7], str[8], str[9], str[10],
			str[11], str[12], str[13], str[14], str[15]);
}

void							otool_content_default_32(
		struct s_otool *const otool,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_section *const section)
{
	struct section *const		rawsection = (void*)section->sectname;
	uint32_t					addr;
	size_t						req;
	char						*str;

	addr = rawsection->addr;
	str = section->content;
	req = section->content_size;
	while (req > 16)
	{
		ft_printf(g_printf_rip32[15], addr, str[0], str[1], str[2], str[3], str[4],
				str[5], str[6], str[7], str[8], str[9], str[10],
				str[11], str[12], str[13], str[14], str[15]);
		str += 16;
		addr += 16;
		req -= 16;
	}
	if (req <= 0)
		return ;
	ft_printf(g_printf_rip32[req - 1], addr, str[0], str[1], str[2], str[3], str[4],
			str[5], str[6], str[7], str[8], str[9], str[10],
			str[11], str[12], str[13], str[14], str[15]);
}
