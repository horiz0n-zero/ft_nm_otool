/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_read_categories.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 10:22:53 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/06 12:26:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static void						read_category(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_category *const cat)
{
	struct s_section *const		s = section_addr_location(macho, cat->value);

	if (s)
	{
		cat->category = section_addr_offset(macho, s, cat->value);
		if (macho->isswap)
			swap_category(cat->category);
		cat->name = section_addr_name(macho, cat->category->name);
		if (cat->category->instance_methods)
			dumper_read_methods(macho, cat->category->instance_methods, &cat->instance_methods, &cat->instance_methods_count);
		if (cat->category->class_methods)
			dumper_read_methods(macho, cat->category->class_methods, &cat->class_methods, &cat->class_methods_count);
		if (cat->category->protocols)
			read_protocols(bin, macho, cat->category->protocols, &cat->protocols, &cat->protocols_count);
		if (cat->category->instance_properties)
			dumper_read_properties(macho, cat->category->instance_properties, &cat->properties, &cat->properties_count);
	}
}

void							dumper_read_categories(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho)
{
	uint64_t *const				end = (void*)(((char*)dumper->cat_list->content) + dumper->cat_list->content_size);
	uint64_t					*ptr;
	int							count;
	struct s_category			*cat;

	count = (int)((dumper->cat_list->content_size / sizeof(uint64_t)));
	if (!(cat = ft_memalloc(sizeof(struct s_category) * (size_t)count)))
		return (set_error(bin, MRERR_MEM));
	ptr = dumper->cat_list->content;
	dumper->categories = cat;
	dumper->categories_count = count;
	while (ptr < end)
	{
		if (macho->isswap)
			cat->value = __builtin_bswap64(*ptr++);
		else
			cat->value = *ptr++;
		read_category(dumper, bin, macho, cat);
		if (bin->error)
			break ;
		++cat;
	}
}









