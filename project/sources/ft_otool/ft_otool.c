/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:57:45 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/18 13:14:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>

void							print_macho(struct s_macho_binary *const bin, struct s_macho *const machos)
{ // pure macho
	struct s_loadcommand		*lc;
	int							lcindex;

	ft_printf("macho : is32(%d), isSwap(%d) %s %s [%s(%s)]\n", machos->is32, machos->isswap,
		get_macho_filetype(machos->header->filetype), get_macho_header_flags(machos->header->flags),
		get_cputype(machos->header->cputype), get_cpusubtype(machos->header->cputype, machos->header->cpusubtype));
	lc = machos->loadcommands;
	if (lc)
	{
		lcindex = 0;
		while (lcindex < machos->loadcommands_count)
		{
			printf("%#08lx %-4zd %s\n", (long)lc->content - (long)bin->content, lc->size, lc->type);
			if (lc->segment)
			{
				ft_printf("-> %s\n", lc->segment->name);
			}
			lcindex++;
			lc++;
		}
	}
}

void							ft_loop_machos(struct s_macho_binary *const bin, struct s_macho *machos, int count)
{
	struct s_loadcommand		*lc;
	int							lcindex;
	struct s_staticlib_macho	*statics;

	while (count--)
	{
		if (machos->statics)
		{
			ft_printf("macho statics : count(%d)\n", machos->statics_count);
			statics = machos->statics;
			while (statics)
			{
				ft_printf("(%s)", statics->name);
				print_macho(bin, statics->macho);
				statics = statics->next;
			}
		}
		else
			print_macho(bin, machos);
		machos++;
	}
}

int								main(int argc, char **argv)
{
	struct s_macho_binary		*bin;

	bin = get_macho_binary(*++argv);
	if (bin->error)
		write(STDOUT_FILENO, bin->error, ft_strlen(bin->error));
	else
	{
		if (bin->count > 1)
		{
			ft_printf("file is fat : is32(%d), isSwap(%d)\n", bin->is32, bin->isswap);
		}
		ft_loop_machos(bin, bin->macho, bin->count);
	}
	unget_macho_binary(bin);
	return (0);
}
