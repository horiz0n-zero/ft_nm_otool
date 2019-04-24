/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 08:35:46 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/23 08:50:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

void						ft_memmove(
		const void *src,
		void *dst,
		size_t size)
{
	size_t					c;

	c = size / sizeof(uint64_t);
	size = size - c;
	while (c--)
	{
		*((uint64_t*)dst) = *((uint64_t*)src);
		dst = (((uint64_t*)dst) + 1);
		src = (((uint64_t*)src) + 1);
	}
	while (size--)
	{
		*((uint8_t*)dst) = *((uint8_t*)src);
		dst = (((uint8_t*)dst) + 1);
		src = (((uint8_t*)src) + 1);
	}
}
