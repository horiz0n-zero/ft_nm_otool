/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:36:24 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/18 12:39:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

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
