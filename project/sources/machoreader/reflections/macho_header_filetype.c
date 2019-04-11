/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_header_filetype.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:39:44 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/11 15:58:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_reflections.h"

static const char			*g_filetypes[] =
{
	"OBJECT",
	"EXECUTE",
	"FVMLIB",
	"CORE",
	"PRELOAD",
	"DYLIB",
	"DYLINKER",
	"BUNDLE",
	"DYLIB_STUB",
	"DSYM",
	"KEXT_BUNDLE"
};

const char					*get_macho_filetype(const uint32_t type)
{
	if (type > (sizeof(g_filetypes) / sizeof(g_filetypes[0])))
		return (NULL);
	return (g_filetypes[type - 1]);
}
