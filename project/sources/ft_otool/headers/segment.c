/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 09:53:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 10:34:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void							print_segment64(struct s_loadcommand *const lc)
{
	struct segment_command_64	*const s = lc->content;

	ft_printf("%22s %s\n", "segname", s->segname);
	ft_printf("%22s 0x%016llx\n", "vmaddr", s->vmaddr);
	ft_printf("%22s 0x%016llx\n", "vmsize", s->vmsize);
	ft_printf("%22s %llu\n", "fileoff", s->fileoff);
	ft_printf("%22s %llu\n", "filesize", s->filesize);
	ft_printf("%22s 0x%08x\n", "maxprot", s->maxprot);
	ft_printf("%22s 0x%08x\n", "initprot", s->initprot);
	ft_printf("%22s %u\n", "nsects", s->nsects);
	ft_printf("%22s 0x%x\n", "flags", s->flags);
}

void							print_segment(struct s_loadcommand *const lc)
{
	struct segment_command		*const s = lc->content;

	ft_printf("%22s %s\n", "segname", s->segname);
	ft_printf("%22s 0x%08x\n", "vmaddr", s->vmaddr);
	ft_printf("%22s 0x%08x\n", "vmsize", s->vmsize);
	ft_printf("%22s %u\n", "fileoff", s->fileoff);
	ft_printf("%22s %u\n", "filesize", s->filesize);
	ft_printf("%22s 0x%08x\n", "maxprot", s->maxprot);
	ft_printf("%22s 0x%08x\n", "initprot", s->initprot);
	ft_printf("%22s %u\n", "nsects", s->nsects);
	ft_printf("%22s 0x%x\n", "flags", s->flags);
}
