/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_static_lib_utility.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 09:02:24 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/21 12:53:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

size_t							get_fat_arch_offset(struct s_macho_binary *const binary, int offindex)
{
	setoffset_object(binary, sizeof(struct fat_header));
	if (binary->is32)
		return ((size_t)((struct fat_arch*)binary->position)[offindex].offset);
	return ((size_t)((struct fat_arch_64*)binary->position)[offindex].offset);
}

int								get_macho_index(struct s_macho_binary *const binary,
		struct s_macho *const m)
{
	int							index;
	struct s_macho				*current;

	current = binary->macho;
	index = 0;
	while (index < binary->count)
	{
		if (current == m)
			return (index);
		index++;
		current++;
	}
	return (0);
}

void							*add_statics(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_staticlib_macho *statics)
{
	if (!statics)
	{
		if (!(macho->statics = ft_memalloc(sizeof(struct s_staticlib_macho))))
			return (set_error_nil(binary, MRERR_MEM));
		macho->statics_count = 1;
		return (macho->statics);
	}
	while (statics->next)
		statics = statics->next;
	if (!(statics->next = ft_memalloc(sizeof(struct s_staticlib_macho))))
		return (set_error_nil(binary, MRERR_MEM));
	macho->statics_count++;
	return (statics->next);
}

int								got_statics(
		struct s_staticlib_macho *statics,
		const uint32_t ran_off)
{
	while (statics)
	{
		if (statics->ran->ran_off == ran_off)
			return (1);
		statics = statics->next;
	}
	return (0);
}
