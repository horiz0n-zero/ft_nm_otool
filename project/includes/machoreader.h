/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:52:27 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/12 15:49:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHOREADER_H
# define MACHOREADER_H

# include <stdio.h>

# include "machoreader_shared.h"
# include "machoreader_reflections.h"

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
	struct s_loadcommand						*loadcommands;
	int											loadcommands_count;
	int											pad;
};
struct											s_segment
{
	char										*name;
};
struct											s_loadcommand
{
	const char									*type;
	void										*content;
	size_t										size;
	struct s_segment							*segments;
};


struct s_macho_binary							*get_macho_binary(const char *file);
void											unget_macho_binary(struct s_macho_binary *const binary);

int												read_fat_header(struct s_macho_binary *const binary, struct fat_header *const header);
void											read_macho_header(struct s_macho_binary *const binary, struct s_macho *const macho);
void											read_static_lib(struct s_macho_binary *const binary, struct s_macho *const macho);

extern void										*get_object(struct s_macho_binary *const binary, void *const seek, const size_t size);
extern void										set_object(struct s_macho_binary *const binary, const size_t size);
extern void										*getset_object(struct s_macho_binary *const binary, void **const seek, const size_t size);
extern void										*align_object(struct s_macho_binary *const binary, const size_t alignment);
extern void										*offset_object(struct s_macho_binary *const binary, const size_t size);
extern void										*setoffset_object(struct s_macho_binary *const binary, const size_t size);

# define GETO(binary, seek, type) get_object(binary, seek, sizeof(type))
# define GETSETO(binary, seek, type) getset_object(binary, seek, sizeof(type))
# define SETO(binary, type) set_object(binary, sizeof(type))

# define GET(binary, seek, size) get_object(binary, seek, (size_t)size)
# define GETSET(binary, seek, size) getset_object(binary, seek, (size_t)size)
# define SET(binary, size) set_object(binary, (size_t)size)

# define AS(ptr, type) ((type*)ptr)
# define MSWAP64(ptr, type) mem_swap64(ptr, sizeof(type) / sizeof(uint64_t))
# define MSWAP32(ptr, type) mem_swap32(ptr, sizeof(type) / sizeof(uint32_t))

// exception
void											set_error(struct s_macho_binary *const binary, const char *const error);
void											*set_error_nil(struct s_macho_binary *const binary, const char *const error);

#endif
