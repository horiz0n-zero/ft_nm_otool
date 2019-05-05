/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_properties.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:20:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/05 14:25:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void							dumper_read_properties(
		struct s_macho *const macho,
		const uint64_t value,
		struct s_property **const property, int *const count)
{
	struct s_section			*s;
	struct s_objc_list_header	*h;
	struct s_objc_property		*properties;
	int							index;

	if (value && (s = section_addr_location(macho, value)))
	{
		h = section_addr_offset(macho, s, value);
		if (macho->isswap)
			swap_list_header(h);
		*count = (int)h->count;
		if (!(*property = ft_memalloc(sizeof(struct s_property) * *count)))
			dumper_fatal("cannot allocate\n");
		properties = (void*)(h + 1);
		index = 0;
		while (index < *count)
		{
			if (macho->isswap)
				swap_property(properties);
			(*property)[index].property = properties;
			(*property)[index].name = section_addr_name(macho, properties->name);
			(*property)[index].attributes = section_addr_name(macho, properties->attributes);
			properties++;
			index++;
		}
	}
}
