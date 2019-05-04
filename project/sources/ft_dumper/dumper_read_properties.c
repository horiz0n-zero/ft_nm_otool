/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_properties.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:20:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 16:35:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void							dumper_read_properties(
		struct s_dumper *const dumper,
		struct s_macho *const macho,
		struct s_class *const c)
{
	struct s_section			*s;
	struct s_objc_list_header	*h;
	struct s_objc_property		*properties;
	int							index;

	if (c->ro->base_properties && (s = section_addr_location(macho, c->ro->base_properties)))
	{
		h = section_addr_offset(macho, s, c->ro->base_properties);
		if (macho->isswap)
			swap_list_header(h);
		c->properties_count = (int)h->count;
		if (!(c->properties = ft_memalloc(sizeof(struct s_property) * c->properties_count)))
			dumper_fatal("cannot allocate\n");
		properties = (void*)(h + 1);
		index = 0;
		while (index < c->properties_count)
		{
			if (macho->isswap)
				swap_property(properties);
			c->properties[index].property = properties;
			c->properties[index].name = section_addr_name(macho, properties->name);
			c->properties[index].attributes = section_addr_name(macho, properties->attributes);
			properties++;
			index++;
		}
	}
}
