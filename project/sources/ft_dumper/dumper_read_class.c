/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_class.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 10:54:11 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/02 16:27:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static struct s_section				*class_section_location(
		struct s_macho *const macho,
		struct s_class *const c)
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
			if (c->value >= addr && c->value <= addr_end)
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
			if (c->value >= addr && c->value <= addr_end)
				return (macho->sections[index]);
		}
	}
	return (NULL);
}

void								read_class(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_class *const c)
{
	char							*ptr;
	struct s_section *const			section = class_section_location(macho, c);
	/*
	ptr = ((char*)macho->header) + class->value;
	class->class = (void*)ptr;
	class->isswift = class->class->data & 0x1;
	class->class->data = class->class->data & ~7;
	ptr = ((char*)macho->header) + class->class->data;
	class->ro = (void*)ptr;*/
}

void								dumper_read_class(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	uint64_t *const					end_file = (void*)(((char*)dumper->class_list->content) + dumper->class_list->content_size);
	uint64_t						*ptr;
	int								count;
	struct s_class					*class;

	count = (int)(dumper->class_list->content_size / sizeof(uint64_t));
	if (!(class = ft_memalloc(sizeof(struct s_class) * (size_t)count)))
		return (set_error(bin, MRERR_MEM));
	ptr = dumper->class_list->content;
	dumper->class_count = count;
	dumper->class = class;
	while (ptr < end_file)
	{
		class->value = *ptr++;
		read_class(dumper, bin, macho, class);
		if (bin->error)
			break ;
		++class;
	}
}
