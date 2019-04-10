/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:57:45 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 13:50:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>

void							ft_loop_machos(struct s_macho_binary *const bin)
{
	struct s_macho				*machos;
	int							count;

	count = bin->count;
	machos = bin->macho;
	while (count--)
	{
		printf("macho : is32(%d), isSwap(%d)\n", machos->is32, machos->isswap);

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
