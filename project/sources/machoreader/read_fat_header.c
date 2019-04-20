/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fat_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:22:35 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 17:49:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void						loop_fat_header64(struct s_macho_binary *const binary,
		int count)
{
	fatalerror("header 64 for fat architecture todo");
}

static void						loop_fat_header32(struct s_macho_binary *const binary,
		int count)
{
	struct fat_arch				*arch;
	void						*arch_position;
	struct s_macho				*current;

	binary->macho = ft_memalloc(sizeof(struct s_macho) * (size_t)count);
	current = binary->macho;
	arch_position = binary->position;
	while (count--)
	{
		if (!(arch = GETSETO(binary, &arch_position, struct fat_arch)))
			return (set_error(binary, "arch size <"));
		MSWAP32(arch, struct fat_arch); // illogic align || align == offset
		setoffset_object(binary, (size_t)arch->offset);
		read_macho_header(binary, current++);
		if (binary->error)
			return ;
	}
}

int							read_fat_header(struct s_macho_binary *const binary,
		struct fat_header *const header)
{
	if (header->magic == FAT_MAGIC || header->magic == FAT_CIGAM)
	{
		binary->is32 = 1;
		binary->isfat = 1;
		if ((binary->isswap = (header->magic == FAT_CIGAM) ? 1 : 0))
			MSWAP32(binary->content, struct fat_header);
		SETO(binary, struct fat_header);
		loop_fat_header32(binary, (binary->count = (int)header->nfat_arch));
		return (1);
	}
	else if (header->magic == FAT_MAGIC_64 || header->magic == FAT_CIGAM_64)
	{
		binary->is32 = 0;
		binary->isfat = 1;
		if ((binary->isswap = (header->magic == FAT_CIGAM_64) ? 1 : 0))
			MSWAP64(binary->content, struct fat_header);
		SETO(binary, struct fat_header);
		loop_fat_header64(binary, (binary->count = (int)header->nfat_arch));
		return (1);
	} // count == 1 ? don't care about is32 & isswap
	return (0);
}
