/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:22:20 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 11:22:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

uint32_t		atoi_print(uint64_t *const value, const char *const src,
		uint32_t index)
{
	uint64_t	raw;

	raw = 0;
	while (src[index] >= '0' && src[index] <= '9')
		raw = raw * 10 + (((uint64_t)(src[index++] - '0')) & 0xFF);
	*value = raw;
	return (index);
}
