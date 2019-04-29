/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_segment_sections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:38:10 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 09:34:03 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

void						set_macho_sections(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	int						index;
	int						i;
	struct s_loadcommand	*lc;
	struct s_section		**ptr;

	if (!(macho->sections = ft_memalloc(sizeof(void*) * macho->sections_count)))
		return (set_error(binary, MRERR_MEM));
	ptr = macho->sections;
	index = 0;
	while (index < macho->loadcommands_count)
	{
		lc = macho->loadcommands + index++;
		if (lc->segment)
		{
			i = 0;
			while (i < lc->segment->count)
				*ptr++ = lc->segment->sections + i++;
		}
	}
}

static inline void			segment_section_32(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const loadc,
		struct s_section *const section)
{
	struct section			*sc;

	sc = binary->position;
	set_object(binary, sizeof(struct section));
	if (macho->isswap)
		swap_section32(sc);
	section->sectname = sc->sectname;
	section->segname = sc->segname;
	section->content = (((char*)macho->header) + sc->offset);
	section->content_size = (size_t)sc->size;
	if (!get_object(binary, macho->header, (size_t)sc->offset + section->content_size))
		return (set_error(binary, MRERR_MACHO));
}

static inline void			segment_section_64(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const loadc,
		struct s_section *const section)
{
	struct section_64		*sc;

	sc = binary->position;
	set_object(binary, sizeof(struct section_64));
	if (macho->isswap)
		swap_section64(sc);
	section->sectname = sc->sectname;
	section->segname = sc->segname;
	section->content = (((char*)macho->header) + sc->offset);
	section->content_size = (size_t)sc->size;
	if (!get_object(binary, macho->header, (size_t)sc->offset + section->content_size))
		return (set_error(binary, MRERR_MACHO));
}

void						read_macho_segment_sections(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const loadc)
{
	int						index;

	index = 0;
	if (macho->is32)
		binary->position = (((char*)loadc->content) + sizeof(struct segment_command));
	else
		binary->position = (((char*)loadc->content) + sizeof(struct segment_command_64));
	if (!(loadc->segment->sections = ft_memalloc(sizeof(struct s_section) * loadc->segment->count)))
		return (set_error(binary, MRERR_MEM));
	while (index < loadc->segment->count)
	{
		if (macho->is32)
			segment_section_32(binary, macho, loadc, loadc->segment->sections + index);
		else
			segment_section_64(binary, macho, loadc, loadc->segment->sections + index);
		if (binary->error)
			return ;
		++index;
	}
	macho->sections_count += loadc->segment->count;
}
