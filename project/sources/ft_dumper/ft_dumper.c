/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:04:06 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/18 13:45:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static void					process(struct s_macho_binary *const bin)
{
	int						index;
	struct s_macho			*macho;
	struct s_loadcommand	*lc;
	struct symtab_command	*sc;

	index = 0;
	while (index < bin->count)
	{
		macho = bin->macho + index++;
		if ((lc = get_macho_first_loadcommand(macho, LC_SYMTAB)))
		{
			sc = get_lc_symtab(macho, lc->content);
			ft_printf("%u %u %u %u\n", sc->symoff, sc->nsyms, sc->stroff, sc->strsize);
		}
		else
			ft_fprintf(STDERR_FILENO, "no symtab found\n");
	}
}

int							main(int argc, char **argv)
{
	char					*error;
	int						flags;
	struct s_macho_binary	*bin;

	flags = 0;
	if (*++argv)
	{
		bin = get_macho_binary(*argv);
		if (bin->error)
			write(STDERR_FILENO, bin->error, ft_strlen(bin->error));
		else
			process(bin);
	}
	return (0);
}
