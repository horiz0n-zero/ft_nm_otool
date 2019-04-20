/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:04:06 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 17:52:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static void					print_symtab(struct s_macho *const macho)
{
	int						index;

	index = 0;
	while (index < macho->symbols_count)
	{
		if (macho->symbols[index].section)
		{
			ft_printf("(%s, %s) %s\n", macho->symbols[index].section->sectname,
					macho->symbols[index].section->segname, macho->symbols[index].name);
		}
		else
		{
			ft_printf("external %s\n", macho->symbols[index].name);
		}
		index++;
	}
}

static void					read_statics(struct s_staticlib_macho *m)
{
	while (m)
	{
		ft_printf("%s:\n", m->name);
		print_symtab(m->macho);
		m = m->next;
	}
}

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
		if (macho->statics)
		{
			read_statics(macho->statics);
		}
		else
			print_symtab(macho);
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
