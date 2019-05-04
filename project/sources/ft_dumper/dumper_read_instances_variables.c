/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_instances_variables.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:47:12 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 15:32:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void							dumper_read_instances(
		struct s_dumper *const dumper,
		struct s_macho *const macho,
		struct s_class *const c)
{
	struct s_section			*s;
	struct s_objc_list_header	*h;
	struct s_objc_ivar			*ivar;
	int							index;

	if (c->ro->ivars && (s = section_addr_location(macho, c->ro->ivars)))
	{
		h = section_addr_offset(macho, s, c->ro->ivars);
		if (macho->isswap)
			swap_list_header(h);
		c->instances_count = (int)h->count;
		if (!(c->instances = ft_memalloc(sizeof(struct s_instance_var) * c->instances_count)))
			dumper_fatal("cannot allocate\n");
		ivar = (void*)(h + 1);
		index = 0;
		while (index < c->instances_count)
		{
			if (macho->isswap)
				swap_ivar(ivar);
			c->instances[index].ivar = ivar;
			c->instances[index].name = section_addr_name(macho, ivar->name);
			c->instances[index].type = section_addr_name(macho, ivar->type);
			ivar++;
			index++;
		}
	}
}




