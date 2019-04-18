/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_segment_sections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:38:10 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/17 13:08:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

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
	{
		swap_section32(sc);
	}
	section->sectname = sc->sectname;
	section->segname = sc->segname;
	section->content = (((char*)macho->header) + sc->offset);
	section->content_size = (size_t)sc->size;
	if (!get_object(binary, macho->header, (size_t)sc->offset + section->content_size))
		return (set_error(binary, "bad section offset"));
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
	{
		swap_section64(sc);
	}
	section->sectname = sc->sectname;
	section->segname = sc->segname;
	section->content = (((char*)macho->header) + sc->offset);
	section->content_size = (size_t)sc->size;
	if (!get_object(binary, macho->header, (size_t)sc->offset + section->content_size))
		return (set_error(binary, "bad section offset"));
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
	loadc->segment->sections = ft_memalloc(sizeof(struct s_section) * loadc->segment->count);
	while (index < loadc->segment->count)
	{
		if (macho->is32)
		{
			segment_section_32(binary, macho, loadc, loadc->segment->sections + index);
		}
		else
		{
			segment_section_64(binary, macho, loadc, loadc->segment->sections + index);
		}
		if (binary->error)
			return ;
		++index;
	}
}



