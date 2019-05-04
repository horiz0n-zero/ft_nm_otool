/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_process_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:27:15 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 10:54:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static inline void				otool_proc_macho(
		struct s_otool *const otool,
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	struct s_section			*section;

	if (otool->flags & (OTOOL_P | OTOOL_H))
	{
		if (otool->flags & OTOOL_P)
			otool_private_header(otool, macho);
		if (otool->flags & OTOOL_H)
			otool_headers(otool, macho);
	}
	else if ((section = get_macho_section(macho, SEG_TEXT, SECT_TEXT)))
	{
		ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
		if (macho->is32)
			otool->content32(otool, bin, macho, section);
		else
			otool->content64(otool, bin, macho, section);
	}
}

static inline void				otool_process_statics(
		struct s_otool *const otool,
		struct s_macho_binary *const bin,
		struct s_staticlib_macho *s)
{
	ft_printf("Archive: %s\n", bin->file);
	while (s)
	{
		ft_printf("%s(%s):\n", bin->file, s->name);
		otool_proc_macho(otool, bin, s->macho);
		s = s->next;
	}
}

static inline void				otool_process_file(
		struct s_otool *const otool,
		struct s_macho_binary *const bin)
{
	int							index;
	int							select;
	struct s_macho				*ptr;

	index = select_arch(bin, &select);
	while (index < bin->count)
	{
		ptr = bin->macho + index++;
		if (ptr->statics)
			otool_process_statics(otool, bin, ptr->statics);
		else
		{
			if (bin->count > 1 && !select)
				ft_printf("%s (architecture %s):\n", bin->file,
								get_cputype(ptr->header->cputype, 1));
			else
				ft_printf("%s:\n", bin->file);
			otool_proc_macho(otool, bin, ptr);
		}
		if (select)
			break ;
	}
}

void							otool_process_files(
		struct s_otool *const otool,
		char **argv)
{
	struct s_macho_binary		*bin;

	while (*argv)
	{
		bin = get_macho_binary(*argv++);
		if (bin->error)
		{
			ft_fprintf(STDERR_FILENO, "ft_otool: \'%s\': %s.\n", bin->file, bin->error);
			continue ;
		}
		otool_process_file(otool, bin);
		unget_macho_binary(bin);
	}
}
