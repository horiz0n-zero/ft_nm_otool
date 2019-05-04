/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_methods.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:02:09 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 15:09:00 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void						dumper_read_methods(
		struct s_dumper *const dumper,
		struct s_macho *const macho,
		struct s_class *const c)
{
	struct s_section			*s;
	struct s_objc_list_header	*list;
	struct s_objc_method		*method;
	int							index;

	if (c->ro->base_methods && (s = section_addr_location(macho, c->ro->base_methods)))
	{
		list = section_addr_offset(macho, s, c->ro->base_methods);
		if (macho->isswap)
			swap_list_header(list);
		list->entsize = list->entsize & ~3;
		c->methods_count = (int)list->count;
		if (!(c->methods = ft_memalloc(sizeof(struct s_method) * c->methods_count)))
			dumper_fatal("cannot allocate\n");
		index = 0;
		method = (void*)(list + 1);
		while (index < c->methods_count)
		{
			if (macho->isswap)
				swap_method(method);
			c->methods[index].method = method;
			c->methods[index].name = section_addr_name(macho, method->name);
			c->methods[index].types = section_addr_name(macho, method->types);
			index++;
			method++;
		}
	}
}





