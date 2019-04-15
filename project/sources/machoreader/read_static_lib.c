/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_static_lib.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:31:55 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/15 14:14:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void						read_static_lib_object(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct s_staticlib_macho *const staticmacho,
		const uint32_t ran_off)
{
	struct ar_hdr				*header;
	size_t						len;

	if (binary->isfat)
	{
		if (!setoffset_object(binary, (size_t)ran_off + get_fat_arch_offset(binary, get_macho_index(binary, macho))))
			return (set_error(binary, "bad fat_arch offset"));
	}
	else if (!setoffset_object(binary, (size_t)ran_off))
		return (set_error(binary, "bad ran_off < size"));
	if (!(header = getset_object(binary, &binary->position, sizeof(struct ar_hdr))))
		return (set_error(binary, "header <"));
	if (!get_object(binary, binary->position, sizeof(struct mach_header_64)))
		return (set_error(binary, "header < + string")); // protection
	len = ft_strlen(binary->position);
	staticmacho->name = binary->position;
	binary->position = (((char*)binary->position) + len);
	while (!*(char*)binary->position)
		binary->position = (((char*)binary->position) + 1);
	printf("ran_off:(%u) max:(%d) %s\n", ran_off, macho->statics_count, staticmacho->name);
	fflush(stdout);
	staticmacho->macho = ft_memalloc(sizeof(struct s_macho));
	read_macho_header(binary, staticmacho->macho);
}

static void						read_static_lib_iter(
		struct s_macho_binary *const binary,
		struct s_macho *const macho,
		struct ranlib *ptr, void *const end_ptr)
{
	int							index;
	struct s_staticlib_macho	*new;

	macho->statics_count = 0;
	while ((ptrdiff_t)ptr < (ptrdiff_t)end_ptr)
	{
		if (!got_statics(macho->statics, ptr->ran_off))
		{
			new = add_statics(binary, macho, macho->statics);
			new->ran = ptr;
			read_static_lib_object(binary, macho, new, ptr->ran_off);
		}
		ptr++;
	}
}

static void						read_static_lib_symbol_table(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	uint32_t					size;

	if (!align_object(binary, sizeof(uint64_t)))
		return (set_error(binary, "cannot align after symdef"));
	if (!get_object(binary, binary->position, sizeof(uint32_t)))
		return (set_error(binary, "cannot read symbol table size"));
	size = *(uint32_t*)binary->position;
	set_object(binary, sizeof(uint32_t));
	if (!get_object(binary, binary->position, (size_t)size))
		return (set_error(binary, "bad symbol table size readed from static lib"));
	read_static_lib_iter(binary, macho, binary->position, (((char*)binary->position) + size));
}

void							read_static_lib(
		struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	struct ar_hdr				*header;

	if (!(header = GETSETO(binary, &binary->position, struct ar_hdr)))
		return (set_error(binary, "size < struct ar_hdr"));
	while ((GETSET(binary, &binary->position, 1)) && *(char*)binary->position == ' ')
		continue ;
	if (!GETO(binary, binary->position, ARFMAG) || ft_strncmp(binary->position, ARFMAG, sizeof(ARFMAG) - 1))
		return (set_error(binary, "size < ar_fmag"));
	SET(binary, sizeof(ARFMAG) - 1);
	if (!GETO(binary, binary->position, SYMDEF_64_SORTED))
		return (set_error(binary, "size < SYMDEF max"));
	if (!ft_strncmp(binary->position, SYMDEF_64_SORTED, sizeof(SYMDEF_64_SORTED) - 1))
		SETO(binary, SYMDEF_64_SORTED);
	else if (!ft_strncmp(binary->position, SYMDEF_64, sizeof(SYMDEF_64) - 1))
		SETO(binary, SYMDEF_64);
	else if (!ft_strncmp(binary->position, SYMDEF_SORTED, sizeof(SYMDEF_SORTED) - 1))
		SETO(binary, SYMDEF_SORTED);
	else if (!ft_strncmp(binary->position, SYMDEF, sizeof(SYMDEF) - 1))
		SETO(binary, SYMDEF);
	else
		return (set_error(binary, "no symdef found."));
	// + align zero ?
	read_static_lib_symbol_table(binary, macho);
}
