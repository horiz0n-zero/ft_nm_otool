/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_methods.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:02:09 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/05 14:12:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void						dumper_read_methods(
		struct s_macho *const macho,
		const uint64_t value,
		struct s_method **const methods, int *const count)
{
	struct s_section			*s;
	struct s_objc_list_header	*list;
	struct s_objc_method		*method;
	int							index;

	if (value && (s = section_addr_location(macho, value)))
	{
		list = section_addr_offset(macho, s, value);
		if (macho->isswap)
			swap_list_header(list);
		list->entsize = list->entsize & ~3;
		*count = (int)list->count;
		if (!(*methods = ft_memalloc(sizeof(struct s_method) * *count)))
			dumper_fatal("cannot allocate\n");
		index = 0;
		method = (void*)(list + 1);
		while (index < *count)
		{
			if (macho->isswap)
				swap_method(method);
			(*methods)[index].method = method;
			(*methods)[index].name = section_addr_name(macho, method->name);
			(*methods)[index].types = section_addr_name(macho, method->types);
			index++;
			method++;
		}
	}
}





