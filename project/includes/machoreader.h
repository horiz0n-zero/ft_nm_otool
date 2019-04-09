/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:52:27 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/09 14:48:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHOREADER_H
# define MACHOREADER_H

# include "machoreader_shared.h"
# include <mach-o/arch.h>
# include <mach-o/compact_unwind_encoding.h>
# include <mach-o/dyld.h>
# include <mach-o/dyld_images.h>
# include <mach-o/fat.h>
# include <mach-o/getsect.h>
# include <mach-o/ldsyms.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <mach-o/reloc.h>
# include <mach-o/stab.h>
# include <mach-o/swap.h>

struct											s_macho_binary
{
	const char									*file;
	const char									*content;
	size_t										content_size;
	const char									*error;
	struct s_macho								*macho;
	int											count;
};

struct											s_macho
{
	int											is32;
};

struct s_macho_binary							*get_macho_binary(const char *file);
void											unget_macho_binary(struct s_macho_binary *const binary);

extern const void								*get_object(struct s_macho_binary *const binary, const void *const seek, const size_t size);

# define OBJECT(type, binary, seek) (type*)get_object(binary, seek, sizeof(type))

#endif
