/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader_reflections.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 09:19:23 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 08:59:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHOREADER_REFLECTIONS_H
# define MACHOREADER_REFLECTIONS_H

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
# include <ar.h>

typedef struct s_symbol					t_symbol;
typedef struct s_macho					t_macho;

struct									s_cputype_reflection
{
	cpu_type_t							value;
	const char							*reflection;
	const char							*reflection_small;
};

struct									s_cpusubtype_in
{
	cpu_subtype_t						value;
	const char							*reflection;
};

struct									s_cpusubtype_reflection
{
	cpu_type_t							value;
	int									index;
	int									count;
};

const char								*get_cputype(
		const cpu_type_t cputype,
		const int small);
const char								*get_cpusubtype(
		const cpu_type_t type,
		const cpu_subtype_t cpusubtype);

struct									s_32_reflection
{
	uint32_t							value;
	const char							*reflection;
};

const char								*get_magic(
		const uint32_t magic);

const char								*get_lc(
		const uint32_t cmd);

struct									s_flags32_reflection
{
	const char							*reflection;
	const uint32_t						value;
};
const char								*get_macho_header_flags(
		const uint32_t flags);
const char								*get_macho_filetype(
		const uint32_t type);


const char								*get_nlist_ext(
		struct s_symbol *const symbol);
char									get_nlist_extchar(
		struct s_symbol *const symbol);
const char								*get_nlist_library(
		struct s_macho *const macho,
		struct s_symbol *const symbol);

// swap
extern void								swap_fatarch32(
		struct fat_arch *const arch);
extern void								swap_fatarch64(
		struct fat_arch_64 *const arch);
extern void								swap_fatheader(
		struct fat_header *const fat);
extern void								swap_sc(
		struct segment_command *const sc);
extern void								swap_sc64(
		struct segment_command_64 *const sc);
extern void								swap_section32(
		struct section *const sec);
extern void								swap_section64(
		struct section_64 *const sec);
extern void								swap_lc(
		struct load_command *const lc);
extern void								swap_mach32(
		struct mach_header *const header);
extern void								swap_mach64(
		struct mach_header_64 *const header);

#endif
