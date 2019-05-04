/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_show_lc_encryption.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:57:26 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 11:16:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static void							dumper_encryption_proc(
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	struct s_loadcommand			*lc;
	struct encryption_info_command	*encry;

	lc = get_macho_first_loadcommand(macho, LC_ENCRYPTION_INFO);
	if (!lc)
	{
		lc = get_macho_first_loadcommand(macho, LC_ENCRYPTION_INFO_64);
		if (!lc)
			return ;
	}
	encry = lc->content;
	ft_printf("%p %08x cryptoff  %u\n",
			(ptrdiff_t)encry - (ptrdiff_t)bin->content +
			offsetof(struct encryption_info_command, cryptoff),
			encry->cryptoff, encry->cryptoff);
	ft_printf("%p %08x cryptsize %u\n",
			(ptrdiff_t)encry - (ptrdiff_t)bin->content +
			offsetof(struct encryption_info_command, cryptsize),
			encry->cryptsize, encry->cryptsize);
	ft_printf("%p %08x cryptid   %u\n",
			(ptrdiff_t)encry - (ptrdiff_t)bin->content +
			offsetof(struct encryption_info_command, cryptid),
			encry->cryptid, encry->cryptid);
}

static void							dumper_encryption_macho(
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	struct s_staticlib_macho		*statics;

	if (macho->statics)
	{
		statics = macho->statics;
		while (statics)
		{
			ft_printf("encryption: %s(%s) [ %s ]\n",
					bin->file, statics->name,
					get_cputype(statics->macho->header->cputype, 1));
			dumper_encryption_proc(bin, statics->macho);
			statics = statics->next;
		}
		return ;
	}
	ft_printf("encryption: %s [ %s ]\n", bin->file, get_cputype(macho->header->cputype, 1));
	dumper_encryption_proc(bin, macho);
}

void								dumper_show_lc_encryption(char **argv)
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
			dumper_encryption_macho(bin, bin->macho + index++);
		unget_macho_binary(bin);
	}
}
