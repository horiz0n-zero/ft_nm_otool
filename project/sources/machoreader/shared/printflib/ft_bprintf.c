/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:15:01 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/06 14:20:16 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void					ft_fprintfunction(const char *const src,
		t_printinfo *const info)
{
	int						index;

	index = 0;
	info->total_len--;
	while (index < info->total_len)
	{
		((char*)info->free)[index] = src[index];
		index++;
	}
	((char*)info->free)[index] = 0;
}

int							ft_bprintf(char *buffer, const char *format, ...)
{
	t_printdata				*element;
	t_printinfo				info;
	va_list					args;

	element = NULL;
	info.first_element = &element;
	va_start(args, format);
	info.args = &args;
	info.function = ft_fprintfunction;
	info.total_len = 1;
	info.data = 0;
	info.free = (uint64_t)buffer;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	return ((int)info.total_len);
}
