/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:37:55 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 09:20:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_reflections.h"

static const struct s_32_reflection	g_magics[] =
{
	{MH_MAGIC, "MH_MAGIC_32"},
	{MH_CIGAM, "MH_CIGAM_32"},
	{MH_MAGIC_64, "MH_MAGIC_64"},
	{MH_CIGAM_64, "MH_CIGAM_64"},
	{FAT_MAGIC, "FAT_MAGIC"},
	{FAT_CIGAM, "FAT_CIGAM"},
	{FAT_MAGIC_64, "FAT_MAGIC_64"},
	{FAT_CIGAM_64, "FAT_CIGAM_64"}
};

const char							*get_magic(const uint32_t magic)
{
	int							index;

	index = 0;
	while (index < (sizeof(g_magics) / sizeof(g_magics[0])))
	{
		if (g_magics[index].value == magic)
			return (g_magics[index].reflection);
		index++;
	}
	return ("???");
}
