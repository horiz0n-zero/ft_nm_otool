/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_static_lib_utility.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 09:02:24 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/15 11:57:15 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

int								get_macho_index

void							*add_statics(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_staticlib_macho *statics)
{
	if (!statics)
	{
		macho->statics = ft_memalloc(sizeof(struct s_staticlib_macho));
		macho->statics_count = 1;
		return (macho->statics);
	}
	while (statics->next)
		statics = statics->next;
	statics->next = ft_memalloc(sizeof(struct s_staticlib_macho));
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







