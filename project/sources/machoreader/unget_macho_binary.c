/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unget_macho_binary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:23:22 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/22 16:23:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void					unget_macho(struct s_macho *const macho);

static void					unget_statics(struct s_staticlib_macho *statics)
{
	while (statics)
	{
		unget_macho(statics->macho);
		statics = statics->next;
	}
}

static void					unget_macho(struct s_macho *const macho)
{
	struct s_loadcommand	*ptr;

	if (macho->statics)
		return (unget_statics(macho->statics));
	if (macho->loadcommands)
	{
		ptr = macho->loadcommands;
		while (macho->loadcommands_count--)
		{
			if (ptr->segment)
			{
				if (ptr->segment->sections)
					free(ptr->segment->sections);
				free(ptr->segment);
			}
			ptr++;
		}
		if (macho->sections)
			free(macho->sections);
		if (macho->symbols)
			free(macho->symbols);
		if (macho->loadcommands)
			free(macho->loadcommands);
	}
}

void						unget_macho_binary(struct s_macho_binary *const binary)
{
	int					count;

	if (binary)
	{
		if (binary->macho)
		{
			count = 0;
			while (count < binary->count)
				unget_macho(binary->macho + count++);
			free(binary->macho);
		}
		if (binary->content && binary->content != MAP_FAILED)
			munmap((void*)binary->content, binary->content_size);
	}
}
