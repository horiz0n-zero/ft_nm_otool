/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_instances_variables.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:47:12 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/05 14:18:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void							dumper_read_instances(
		struct s_macho *const macho,
		const uint64_t value,
		struct s_instance_var **const ivars, int *const count)
{
	struct s_section			*s;
	struct s_objc_list_header	*h;
	struct s_objc_ivar			*ivar;
	int							index;

	if (value && (s = section_addr_location(macho, value)))
	{
		h = section_addr_offset(macho, s, value);
		if (macho->isswap)
			swap_list_header(h);
		*count = (int)h->count;
		if (!(*ivars = ft_memalloc(sizeof(struct s_instance_var) * *count)))
			dumper_fatal("cannot allocate\n");
		ivar = (void*)(h + 1);
		index = 0;
		while (index < *count)
		{
			if (macho->isswap)
				swap_ivar(ivar);
			(*ivars)[index].ivar = ivar;
			(*ivars)[index].name = section_addr_name(macho, ivar->name);
			(*ivars)[index].type = section_addr_name(macho, ivar->type);
			ivar++;
			index++;
		}
	}
}




