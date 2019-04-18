/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:04:54 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 12:08:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void					ft_fprintfunction(const char *const src,
		t_printinfo *const info)
{
	info->total_len--;
	info->data = write((int)info->free, src, info->total_len);
}

int							ft_fprintf(const int fd, const char *format, ...)
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
	info.free = (uint64_t)fd;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	return ((int)info.total_len);
}
