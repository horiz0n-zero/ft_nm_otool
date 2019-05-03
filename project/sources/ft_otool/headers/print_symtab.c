/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:40:44 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 13:13:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void								print_symtab(
		struct s_loadcommand *const lc)
{
	struct symtab_command *const	s = lc->content;

	ft_printf("%22s %u\n", "symoff", s->symoff);
	ft_printf("%22s %u\n", "nsyms", s->nsyms);
	ft_printf("%22s %u\n", "stroff", s->stroff);
	ft_printf("%22s %u\n", "strsize", s->strsize);
}

void								print_dysymtab(
		struct s_loadcommand *const lc)
{
	struct dysymtab_command *const	s = lc->content;

	ft_printf("%22s %u\n", "ilocalsym", s->ilocalsym);
	ft_printf("%22s %u\n", "nlocalsym", s->nlocalsym);
	ft_printf("%22s %u\n", "iextdefsym", s->iextdefsym);
	ft_printf("%22s %u\n", "nextdefsym", s->nextdefsym);
	ft_printf("%22s %u\n", "iundefsym", s->iundefsym);
	ft_printf("%22s %u\n", "nundefsym", s->nundefsym);
	ft_printf("%22s %u\n", "tocoff", s->tocoff);
	ft_printf("%22s %u\n", "ntoc", s->ntoc);
	ft_printf("%22s %u\n", "modtaboff", s->modtaboff);
	ft_printf("%22s %u\n", "nmodtab", s->nmodtab);
	ft_printf("%22s %u\n", "extrefsymoff", s->extrefsymoff);
	ft_printf("%22s %u\n", "nextrefsyms", s->nextrefsyms);
	ft_printf("%22s %u\n", "indirectsymoff", s->indirectsymoff);
	ft_printf("%22s %u\n", "nindirectsyms", s->nindirectsyms);
	ft_printf("%22s %u\n", "extreloff", s->extreloff);
	ft_printf("%22s %u\n", "nextrel", s->nextrel);
	ft_printf("%22s %u\n", "locreloff", s->locreloff);
	ft_printf("%22s %u\n", "nlocrel", s->nlocrel);
}
