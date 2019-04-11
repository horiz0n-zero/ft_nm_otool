/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:04:06 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/11 15:51:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static const struct s_argument	g_arguments[256] =
{
	['p'] = {"private-header", 1, 0, NULL},
	['h'] = {"headers", 2, 0, NULL}
};

#include <stdio.h>

static void					loop_machos(struct s_macho_binary *const bin)
{
	int						i;
	struct s_macho			*ptr;

	i = 0;
	while (i < bin->count)
	{
		ptr = bin->macho + i++;
		printf("cpu_type: %s, magic: %s\n", get_cputype(ptr->header->cputype), get_magic(ptr->header->magic));
		printf("type: %s, flags: %s\n", get_macho_filetype(ptr->header->filetype), get_macho_header_flags(ptr->header->flags));
	}
}

int							main(int argc, char **argv)
{
	char					*error;
	int						flags;
	struct s_macho_binary	*bin;

	flags = 0;
	if (!(argv = arguments_get(++argv, g_arguments, &flags, &error)))
		write(STDERR_FILENO, error, ft_strlen(error));
	else
	{
		if (flags & 1 && *argv)
		{
			bin = get_macho_binary(*argv);
			if (bin->error)
				write(STDERR_FILENO, bin->error, ft_strlen(bin->error));
			else
				loop_machos(bin);
		}
	}
	return (0);
}
