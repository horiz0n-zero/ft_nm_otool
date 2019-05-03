/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_linker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:25:03 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 16:37:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void									print_linker_option(
		struct s_loadcommand *const lc)
{
	struct linker_option_command *const	l = lc->content;

	ft_printf("%22s %u\n", "count", l->count);
}

void								print_symseg(
		struct s_loadcommand *const lc)
{
	struct symseg_command *const	l = lc->content;

	ft_printf("%22s %u\n", "offset", l->offset);
	ft_printf("%22s %u\n", "size", l->size);
}

void								print_fvmfile_command(
		struct s_loadcommand *const lc)
{
	struct fvmfile_command *const	f = lc->content;

	ft_printf("%22s %s\n", "name", ((char*)lc->content) +
			f->name.offset);
	ft_printf("%22s %u\n", "header_addr", f->header_addr);
}

void								print_main(
		struct s_loadcommand *const lc)
{
	struct entry_point_command		*p;

	p = lc->content;
	ft_printf("%22s %llu\n", "entryoff", p->entryoff);
	ft_printf("%22s %llu\n", "stacksize", p->stacksize);
}
