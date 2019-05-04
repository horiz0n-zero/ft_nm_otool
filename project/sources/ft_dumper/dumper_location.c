/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_location.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 11:47:44 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 13:46:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

char								*section_addr_name(
		struct s_macho *const macho,
		const uint64_t value)
{
	struct s_section *const			s = section_addr_location(macho, value);

	if (s)
		return (section_addr_offset(macho, s, value));
	return (NULL);
}

void								*section_addr_offset(
		struct s_macho *const macho,
		struct s_section *const section,
		const uint64_t value)
{
	uint64_t						offset;

	if (macho->is32)
	{
		offset = value - (uint64_t)((struct section*)section->sectname)->addr;
		return (((char*)section->content) + offset);
	}
	else
	{
		offset = value - ((struct section_64*)section->sectname)->addr;
		return (((char*)section->content) + offset);
	}
}

struct s_section					*section_addr_location(
		struct s_macho *const macho,
		const uint64_t value)
{
	int								index;
	uint64_t						addr;
	uint64_t						addr_end;

	index = -1;
	if (macho->is32)
	{
		while (++index < macho->sections_count)
		{
			addr = (uint64_t)
				((struct section*)macho->sections[index]->sectname)->addr;
			addr_end = addr + (uint64_t)
				((struct section*)macho->sections[index]->sectname)->size;
			if (value >= addr && value <= addr_end)
				return (macho->sections[index]);
		}
	}
	else
	{
		while (++index < macho->sections_count)
		{
			addr =
				((struct section_64*)macho->sections[index]->sectname)->addr;
			addr_end = addr +
				((struct section_64*)macho->sections[index]->sectname)->size;
			if (value >= addr && value <= addr_end)
				return (macho->sections[index]);
		}
	}
	return (NULL);
}
