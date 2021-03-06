/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:36:24 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/02 09:18:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

struct s_section					*get_macho_section(
		struct s_macho *const macho,
		const char *const segname,
		const char *const sectname)
{
	int								index;
	const int						lseg = (int)ft_strlen(segname);
	const int						lsect = (int)ft_strlen(sectname);

	index = 0;
	while (index < macho->sections_count)
	{
		if (!ft_strncmp(macho->sections[index]->segname, segname, lseg) &&
				!ft_strncmp(macho->sections[index]->sectname, sectname, lsect))
			return (macho->sections[index]);
		++index;
	}
	return (NULL);
}

inline struct s_loadcommand			*get_macho_first_loadcommand(
		struct s_macho *const macho,
		const uint32_t cmdtype)
{
	int								index;

	if (macho->loadcommands)
	{
		index = 0;
		while (index < macho->loadcommands_count)
		{
			if (macho->loadcommands[index].cmdtype == cmdtype)
				return (macho->loadcommands + index);
			index++;
		}
	}
	return (NULL);
}
