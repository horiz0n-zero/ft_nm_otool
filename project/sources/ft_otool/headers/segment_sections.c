/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_sections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 09:22:54 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 10:39:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int32_t				multiple(int32_t v, int32_t r)
{
	if (v < 0 || v >= 16)
		return (r);
	while (--v > 0)
		r *= 2;
	return (r);
}

static inline void			segment_sections64(
		struct section_64*const s)
{
	ft_printf("\n%22s 0x%016llx\n", "addr", s->addr);
	ft_printf("%22s 0x%016llx\n", "size", s->size);
	ft_printf("%22s %u\n", "offset", s->offset);
	ft_printf("%22s 2^%u (%u)\n", "align", s->align, multiple(s->align, 2));
	ft_printf("%22s %u\n", "reloff", s->reloff);
	ft_printf("%22s %u\n", "nreloc", s->nreloc);
	ft_printf("%22s %u\n", "flags", s->flags);
	ft_printf("%22s %u\n", "reserved1", s->reserved1);
	ft_printf("%22s %u\n", "reserved2", s->reserved2);
	ft_printf("%22s %u\n", "reserved3", s->reserved3);
}

void						print_segment_sections64(
		struct s_segment *const segment)
{
	struct section_64		*s;
	int						index;
	int						i;

	index = 0;
	while (index < segment->count)
	{
		ft_printf("Section %d\n", index);
		s = (void*)segment->sections[index++].sectname;
		i = 0;
		while (i < 16 && s->sectname[i])
			i++;
		ft_printf("%22s ", "sectname");
		write(STDOUT_FILENO, s->sectname, (size_t)i);
		ft_printf("\n%22s ", "segname");
		i = 0;
		while (i < 16 && s->segname[i])
			i++;
		write(STDOUT_FILENO, s->segname, (size_t)i);
		segment_sections64(s);
	}
}

static inline void			segment_sections32(
		struct section *const s)
{
	ft_printf("\n%22s 0x%08x\n", "addr", s->addr);
	ft_printf("%22s 0x%08x\n", "size", s->size);
	ft_printf("%22s %u\n", "offset", s->offset);
	ft_printf("%22s 2^%u (%u)\n", "align", s->align, multiple(s->align, 2));
	ft_printf("%22s %u\n", "reloff", s->reloff);
	ft_printf("%22s %u\n", "nreloc", s->nreloc);
	ft_printf("%22s %u\n", "flags", s->flags);
	ft_printf("%22s %u\n", "reserved1", s->reserved1);
	ft_printf("%22s %u\n", "reserved2", s->reserved2);
}

void						print_segment_sections32(
		struct s_segment *const segment)
{
	struct section			*s;
	int						index;
	int						i;

	while (index < segment->count)
	{
		ft_printf("Section %d\n", index);
		s = (void*)segment->sections[index++].sectname;
		i = 0;
		while (i < 16 && s->sectname[i])
			i++;
		ft_printf("%22s ", "sectname");
		write(STDOUT_FILENO, s->sectname, (size_t)i);
		ft_printf("\n%22s ", "segname");
		i = 0;
		while (i < 16 && s->segname[i])
			i++;
		write(STDOUT_FILENO, s->segname, (size_t)i);
		// if m || segment .pad
		segment_sections32(s);
	}
}
