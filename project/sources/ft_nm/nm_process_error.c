/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:12:08 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 10:56:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static const char	*g_usage[] =
{
	"usage:\n\n",
	"-m --multi              Display  the  N_SECT  type symbols (Mach-O symbols) as (segment_name, section_name)\n",
	"                        followed by either external or non-external and then the symbol name.\n",
	"                        Undefined, common, absolute and indirect symbols get displayed as (undefined), (common), (absolute), and (indirect).\n",
	"-o --object             Prepend file or archive element name to each output line, rather than only once.\n",
	"                        This option have priority on -m.\n",
	"-j --just-symbol-name   Just display the symbol names (no value or type).\n",
	"                        This option have priority on -m and -o.\n\n",
	"-c --cstrings           Display only c strings.\n",
	"                        This option have priority on -o and -j.\n",
	"                        With -m this option also print address and length.\n\n",
	"-g --global             Display only global (external) symbols.\n",
	"-u --undefined          Display only undefined symbols.\n",
	"-d --debug              Display also debug entry.\n\n",
	"-n --numeric-sort       Sort numerically rather than alphabetically.\n",
	"-p --preserve-sort      Don't sort; display in symbol-table order.\n",
	"-r --reverse-sort       Sort in reverse order.\n\n",
	"-a --all-arch           Display all architecture available.\n"
};

void				nm_usage(void)
{
	int				index;

	index = 0;
	while (index < (sizeof(g_usage) / sizeof(g_usage[0])))
	{
		write(STDERR_FILENO, g_usage[index], ft_strlen(g_usage[index]));
		index++;
	}
}

void				nm_process_error(struct s_macho_binary *const bin)
{
	ft_fprintf(STDERR_FILENO, "ft_nm: %s: %s.\n\n", bin->file, bin->error);
	unget_macho_binary(bin);
}
