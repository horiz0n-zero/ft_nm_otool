/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_class.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 10:54:11 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/08 10:39:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static char							*search_undefined_superclass(
		struct s_macho *const macho,
		const uint64_t value)
{
	int								i;
	static const char				prefix[] = "_OBJC_CLASS_$_";
	char							*ptr;
	const char						*str;

	i = 0;
	while (i < macho->symbols_count)
	{
		if (macho->symbols[i].value == value)
		{
			ptr = macho->symbols[i].name;
			str = prefix;
			while (*ptr && *str && *str == *ptr)
			{
				ptr++;
				str++;
			}
			if (!*str && *ptr)
				return (ptr);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

static void							read_class(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_class *const c)
{
	struct s_section *const			section = section_addr_location(macho, c->value);

	if (!section)
		dumper_fatal("no section found.\n");
	c->class = section_addr_offset(macho, section, c->value);
	if (macho->isswap)
		swap_class(c->class);
	c->isswift = c->class->data & 0x1;
	c->class->data = c->class->data & ~7;
	if (c->class->data) // do research section ? || don't checked otherwise in methods ...
	{
		c->ro = section_addr_offset(macho, section, c->class->data);
		if (macho->isswap)
			swap_class_ro(c->ro);
		c->name = section_addr_name(macho, c->ro->name);
		dumper_read_methods(macho, c->ro->base_methods, &c->methods, &c->methods_count);
		dumper_read_instances(macho, c->ro->ivars, &c->instances, &c->instances_count);
		dumper_read_properties(macho, c->ro->base_properties, &c->properties, &c->properties_count);
		if (c->ro->base_protocols)
			read_protocols(bin, macho, c->ro->base_protocols, &c->protocols, &c->protocols_count);
		if (c->class->superclass && !(c->ro->flags & RO_META))
		{
			c->superclass = ft_memalloc(sizeof(struct s_class));
			c->superclass->value = c->class->superclass;
			read_class(dumper, bin, macho, c->superclass);
			c->superclass_name = c->superclass->name;
		}
		else if (!(c->ro->flags & RO_META))
			c->superclass_name = search_undefined_superclass(macho, c->value);
		if (c->class->isa && !(c->ro->flags & RO_META))
		{
			c->metaclass = ft_memalloc(sizeof(struct s_class));
			c->metaclass->value = c->class->isa;
			read_class(dumper, bin, macho, c->metaclass);
		}
	}
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
		if (macho->isswap)
			class->value = __builtin_bswap64(*ptr++);
		else
			class->value = *ptr++;
		read_class(dumper, bin, macho, class);
		if (bin->error)
			break ;
		++class;
	}
}
