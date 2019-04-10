/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fat_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:22:35 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 15:14:48 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void						loop_fat_header(struct s_macho_binary *const binary,
		int count)
{
	struct fat_arch				*arch;
	struct fat_arch_64			*arch64;
	struct s_macho				*current;

	binary->macho = malloc(sizeof(struct s_macho) * (size_t)count);
	current = binary->macho;
	printf("loop_(%d)\n", binary->count);
	while (count--)
	{
		if (binary->is32)
			arch = GETSETO(binary, &binary->position, struct fat_arch);
		else
			arch64 = GETSETO(binary, &binary->position, struct fat_arch_64);
		if (!arch)
			return (set_error(binary, "bad macho"));
		printf("align : %u\n", binary->is32 ? arch->align : arch64->align);
		//if (!align_object(binary, (size_t)arch->align))
		//	return ;
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
		if ((binary->isswap = (header->magic == FAT_CIGAM) ? 1 : 0))
			mem_swap32(binary->content, binary->content_size / sizeof(uint64_t));
		SETO(binary, struct fat_header);
		loop_fat_header(binary, (binary->count = (int)header->nfat_arch));
		return (1);
	}
	else if (header->magic == FAT_MAGIC_64 || header->magic == FAT_CIGAM_64)
	{
		binary->is32 = 0;
		if ((binary->isswap = (header->magic == FAT_CIGAM_64) ? 1 : 0))
			mem_swap64(binary->content, binary->content_size / sizeof(uint64_t));
		SETO(binary, struct fat_header);
		loop_fat_header(binary, (binary->count = (int)header->nfat_arch));
		return (1);
	} // count == 1 ? don't care about is32 & isswap
	return (0);
}
