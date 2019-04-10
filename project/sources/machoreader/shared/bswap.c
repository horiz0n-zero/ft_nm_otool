/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bswap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:06:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 15:00:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

void					mem_swap32(void *const content, size_t size)
{
	register uint32_t	*ptr;

	ptr = content;
	while (size--)
	{
		*ptr = __builtin_bswap32(*ptr);
		ptr++;
	}
}

void					mem_swap64(void *const content, size_t size)
{
	register uint64_t	*ptr;

	ptr = content;
	while (size--)
	{
		*ptr = __builtin_bswap64(*ptr);
		ptr++;
	}
}
