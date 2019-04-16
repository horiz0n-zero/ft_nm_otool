/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_macho_segment_sections.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:38:10 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/16 17:38:48 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

void						read_macho_segment_sections(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const loadc)
{
	int						index;
	struct section			*seg;
	struct section_64		*seg64;

	index = 0;
	if (macho->is32)
		binary->position = (((char*)loadc->content) + sizeof(struct segment_command));
	else
		binary->position = (((char*)loadc->content) + sizeof(struct segment_command_64));
	while (index < loadc->segments->count)
	{
		if (macho->is32)
		{
			seg = binary->position;
			if (macho->isswap)
				swap_section32(seg);
			set_object(binary, sizeof(struct section));
			printf("%s, %s :: %u %u\n", seg->sectname, seg->segname, seg->offset, seg->size);
		}
		else
		{
			seg64 = binary->position;
			if (macho->isswap)
				swap_section64(seg64);
			set_object(binary, sizeof(struct section_64));
			printf("%s, %s :: %u %u\n", seg64->sectname, seg64->segname, seg64->offset, seg64->size);
		}
		++index;
	}
}


















