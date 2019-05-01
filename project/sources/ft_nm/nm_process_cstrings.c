/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_cstrings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:07:39 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/01 16:03:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void							cstrings_multi_macho(
		struct s_macho *const macho,
		const char *const segname,
		const char *const sect)
{
	struct s_section				*section;
	char							*ptr;
	char							*end_ptr;

	if ((section = get_macho_section(macho, segname, sect)))
	{
		ft_printf("Section (%s,%s):\n", segname, sect);
		ptr = section->content;
		end_ptr = ptr + section->content_size;
		while (ptr < end_ptr)
		{
			if (macho->is32)
				ft_printf("%08llx %4zd \"%s\"", (ptrdiff_t)ptr - (ptrdiff_t)macho->header, ft_strlen(ptr), ptr);
			else
				ft_printf("%016llx %4zd \"%s\"\n", (ptrdiff_t)ptr - (ptrdiff_t)macho->header, ft_strlen(ptr), ptr);
			while (*ptr && ptr < end_ptr)
				ptr++;
			while (!*ptr && ptr < end_ptr)
				ptr++;
		}
	}
}

static void							cstrings_macho(
		struct s_macho *const macho,
		const char *const segname,
		const char *const sect)
{
	struct s_section				*section;
	char							*ptr;
	char							*end_ptr;

	if ((section = get_macho_section(macho, segname, sect)))
	{
		ft_printf("Section (%s,%s):\n", segname, sect);
		ptr = section->content;
		end_ptr = ptr + section->content_size;
		while (ptr < end_ptr)
		{
			ft_printf("%s\n", ptr);
			while (*ptr && ptr < end_ptr)
				ptr++;
			while (!*ptr && ptr < end_ptr)
				ptr++;
		}
	}
}

static void							cstrings_file(
		const char *const file,
		void (*const proc)(struct s_macho *const macho,
			const char *const segname,
			const char *const section),
		const int multiple)
{
	struct s_macho_binary *const	bin = get_macho_binary(file);
	struct s_staticlib_macho		*statics;
	int								index;

	index = 0;
	if (bin->error)
		return (nm_process_error(bin));
	if (multiple)
		ft_printf("\n%s:\n", file);
	while (index < bin->count)
	{
		if (bin->macho[index].statics)
		{
			statics = bin->macho[index].statics;
			while (statics)
			{
				ft_printf("\n%s(%s):\n", file, statics->name);
				proc(statics->macho, SEG_TEXT, "__cstring");
				proc(statics->macho, SEG_TEXT, "__objc_methname");
				proc(statics->macho, SEG_TEXT, "__objc_classname");
				statics = statics->next;
			}
		}
		else
		{
			proc(bin->macho + index, SEG_TEXT, "__cstring");
			proc(bin->macho + index, SEG_TEXT, "__objc_methname");
			proc(bin->macho + index, SEG_TEXT, "__objc_classname");
		}
		++index;
	}
	unget_macho_binary(bin);
}

void								nm_process_strings(
		struct s_nm *const nm,
		char **argv)
{
	int								multiple;

	if (!*argv)
	{
		if (nm->flags & NM_M)
			cstrings_file(DEFAULT_BIN, cstrings_multi_macho, 0);
		else
			cstrings_file(DEFAULT_BIN, cstrings_macho, 0);
	}
	else
	{
		if (*argv && *(argv + 1))
			multiple = 1;
		else
			multiple = 0;
		if (nm->flags & NM_M)
		{
			while (*argv)
				cstrings_file(*argv++, cstrings_multi_macho, multiple);
		}
		else
		{
			while (*argv)
				cstrings_file(*argv++, cstrings_macho, multiple);
		}
	}
}
