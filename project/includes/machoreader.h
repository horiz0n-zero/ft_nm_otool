/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:52:27 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 14:54:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHOREADER_H
# define MACHOREADER_H

# include <stdio.h>

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

	char										*content;
	size_t										content_size;

	const char									*error;

	void										*position;
	int											is32;
	int											isswap;

	struct s_macho								*macho;
	int											count;
};

struct											s_macho
{
	int											is32;
	int											isswap;

	struct mach_header							*header;
};

struct s_macho_binary							*get_macho_binary(const char *file);
void											unget_macho_binary(struct s_macho_binary *const binary);

int												read_fat_header(struct s_macho_binary *const binary, struct fat_header *const header);
void											read_macho_header(struct s_macho_binary *const binary, struct s_macho *const macho);

extern void										*get_object(struct s_macho_binary *const binary, void *const seek, const size_t size);
extern void										set_object(struct s_macho_binary *const binary, const size_t size);
extern void										*getset_object(struct s_macho_binary *const binary, void **const seek, const size_t size);
extern void										*align_object(struct s_macho_binary *const binary, const size_t alignment);

# define GETO(binary, seek, type) get_object(binary, seek, sizeof(type))
# define GETSETO(binary, seek, type) getset_object(binary, seek, sizeof(type))
# define SETO(binary, type) set_object(binary, sizeof(type))

// exception
void											set_error(struct s_macho_binary *const binary, const char *const error);
void											*set_error_nil(struct s_macho_binary *const binary, const char *const error);

#endif
