/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_show_uuid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:50:35 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/30 17:10:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static void							dumper_uuid_proc(
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	struct s_loadcommand			*lc;
	struct uuid_command				*cmd;

	lc = get_macho_first_loadcommand(macho, LC_UUID);
	if (!lc)
		return ;
	cmd = lc->content;
	ft_printf("%08X-%04hX-%04hX-%04hX-%08X%04hX\n",
			__builtin_bswap32(*(uint32_t*)cmd->uuid),
			__builtin_bswap16(*(uint16_t*)(cmd->uuid + 4)),
			__builtin_bswap16(*(uint16_t*)(cmd->uuid + 6)),
			__builtin_bswap16(*(uint16_t*)(cmd->uuid + 8)),
			__builtin_bswap32(*(uint32_t*)(cmd->uuid + 10)),
			__builtin_bswap16(*(uint16_t*)(cmd->uuid + 14)));
}

static void							dumper_uuid_macho(
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	struct s_staticlib_macho		*statics;

	if (macho->statics)
	{
		statics = macho->statics;
		while (statics)
		{
			ft_printf("uuid: %s(%s) [ %s ]\n",
					bin->file, statics->name,
					get_cputype(statics->macho->header->cputype, 1));
			dumper_uuid_proc(bin, statics->macho);
			statics = statics->next;
		}
		return ;
	}
	ft_printf("uuid: %s [ %s ]\n", bin->file, get_cputype(macho->header->cputype, 1));
	dumper_uuid_proc(bin, macho);
}

void								dumper_show_uuid(char **argv)
{
	static char						*default_argv[] = {"a.out", NULL};
	struct s_macho_binary			*bin;
	int								index;

	if (!*argv)
		argv = default_argv;
	while (*argv)
	{
		bin = get_macho_binary(*argv++);
		if (bin->error)
		{
			ft_fprintf(STDERR_FILENO, "ft_dumper: %s: %s.\n", bin->file, bin->error);
			unget_macho_binary(bin);
			continue ;
		}
		index = 0;
		while (index < bin->count)
			dumper_uuid_macho(bin, bin->macho + index++);
		unget_macho_binary(bin);
	}
}
