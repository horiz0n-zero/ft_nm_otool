/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:57:45 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/12 14:47:29 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>

void							ft_loop_machos(struct s_macho_binary *const bin)
{
	struct s_macho				*machos;
	struct s_loadcommand		*lc;
	int							count;
	int							lcindex;

	count = bin->count;
	machos = bin->macho;
	while (count--)
	{
		printf("macho : is32(%d), isSwap(%d) %s %s [%s]\n", machos->is32, machos->isswap,
				get_macho_filetype(machos->header->filetype), get_macho_header_flags(machos->header->flags),
				get_cputype(machos->header->cputype));
		lc = machos->loadcommands;
		if (lc)
		{
			lcindex = 0;
			while (lcindex < machos->loadcommands_count)
			{
				printf("%#08lx %-4zd %s\n", (long)lc->content - (long)bin->content, lc->size, lc->type);
				if (lc->segments)
				{
					printf("-> %s\n", lc->segments->name);
				}
				lcindex++;
				lc++;
			}
		}
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
			printf("file is fat : is32(%d), isSwap(%d)\n", bin->is32, bin->isswap);
		}
		ft_loop_machos(bin);
	}
	unget_macho_binary(bin);
	return (0);
}
