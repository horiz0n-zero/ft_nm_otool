/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:52:27 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 09:39:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHOREADER_H
# define MACHOREADER_H

# include "machoreader_shared.h"
# include "machoreader_reflections.h"

typedef struct s_macho_binary					t_macho_binary;

typedef struct s_macho							t_macho;
typedef struct s_staticlib_macho				t_staticlib_macho;

typedef struct s_dylib							t_dylib;
typedef struct s_symbol							t_symbol;
typedef struct s_section						t_section;
typedef struct s_segment						t_segment;
typedef struct s_loadcommand					t_loadcommand;

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
	int											isfat;
};

struct											s_macho
{
	int											is32;
	int											isswap;

	struct mach_header							*header;
	struct s_loadcommand						*loadcommands;
	int											loadcommands_count;

	struct s_section							**sections;
	int											sections_count;

	struct s_symbol								*symbols;
	int											symbols_count;

	struct s_dylib								*dylibs;
	int											dylibs_count;

	int											statics_count;
	struct s_staticlib_macho					*statics;
};
struct											s_staticlib_macho
{
	const char									*name;
	struct ranlib								*ran;
	struct s_macho								*macho;
	struct s_staticlib_macho					*next;
};

struct											s_dylib
{
	struct s_loadcommand						*lc;
	char										*path;
	char										*name;
	struct s_dylib								*next;
};
struct											s_symbol
{
	struct s_section							*section;
	char										*name;

	uint8_t										type;
	uint8_t										pad0;
	uint16_t									desc;
	uint32_t									skip;
	uint64_t									value;
};
struct											s_section
{
	char										*sectname;
	char										*segname;

	void										*content;
	size_t										content_size;
};
struct											s_segment
{
	char										*name;

	int											count;
	int											pad;
	struct s_section							*sections;
};
struct											s_loadcommand
{
	const char									*type;
	uint32_t									cmdtype;
	uint32_t									pad; // pad

	void										*content;
	size_t										size;

	struct s_segment							*segment;
};

struct s_macho_binary							*get_macho_binary(
		const char *file);
void											unget_macho_binary(
		struct s_macho_binary *const binary);

int												read_fat_header(
		struct s_macho_binary *const binary,
		struct fat_header *const header);
void											read_macho_header(
		struct s_macho_binary *const binary,
		struct s_macho *const macho);
void											read_macho_segment_sections(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const loadc);
void											set_macho_sections(
		struct s_macho_binary *const binary,
		struct s_macho *const macho);
void											get_macho_dylib(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_loadcommand *const lc);
struct s_dylib									*get_macho_dylib_index(
		struct s_macho *const macho,
		const int index);
void											read_macho_symtab(
		struct s_macho_binary *const binary,
		struct s_macho *const macho);
void											read_static_lib(
		struct s_macho_binary *const binary,
		struct s_macho *const macho);
int												got_statics(
		struct s_staticlib_macho *statics,
		const uint32_t ran_off);
void											*add_statics(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_staticlib_macho *statics);
int												get_macho_index(
		struct s_macho_binary *const binary,
		struct s_macho *const macho);
size_t											get_fat_arch_offset(
		struct s_macho_binary *const binary,
		int offindex);

extern void										*get_object(
		struct s_macho_binary *const binary,
		void *const seek,
		const size_t size);
extern void										set_object(
		struct s_macho_binary *const binary,
		const size_t size);
extern void										*getset_object(
		struct s_macho_binary *const binary,
		void **const seek,
		const size_t size);

extern void										*align_object(
		struct s_macho_binary *const binary,
		const size_t alignment);
extern void										*offset_object(
		struct s_macho_binary *const binary,
		const size_t size);
extern void										*setoffset_object(
		struct s_macho_binary *const binary,
		const size_t size);

extern struct s_loadcommand						*get_macho_first_loadcommand(
		struct s_macho *const macho,
		const uint32_t cmdtype);
struct s_section								*get_macho_section(
		struct s_macho *const macho,
		const char *const segname,
		const char *const sectname);

// sort
void											sort_statics(
		struct s_staticlib_macho *const macho,
		const int count);
void											sort_symbols(
		struct s_symbol *const symbols,
		const int count,
		const int reverse,
		int (*const sortfunc)(struct s_symbol *const a, struct s_symbol *const b));
int												sort_symbols_alpha(
		struct s_symbol *const a,
		struct s_symbol *const b);
int												sort_symbols_numeric(
		struct s_symbol *const a,
		struct s_symbol *const b);


// exception
void											set_error(
		struct s_macho_binary *const binary,
		const char *const error);
void											*set_error_nil(
		struct s_macho_binary *const binary,
		const char *const error);

# define MRERR_MACHO "The file was not recognized as a valid object file"
# define MRERR_DENIED "Permission denied"
# define MRERR_NOTFOUND "No such file or directory"
# define MRERR_ISDIR "Is a directory"
# define MRERR_NOTREF "Is a named type file"
# define MRERR_MEM "Not enough space/cannot allocate memory"

#endif
