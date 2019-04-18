/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:46:29 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 10:50:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void					ft_printfunction(const char *const src,
		t_printinfo *const info)
{
	info->total_len--;
	info->data = write(STDOUT_FILENO, src, info->total_len);
}

int							ft_printf(const char *format, ...)
{
	t_printdata				*element;
	t_printinfo				info;
	va_list					args;

	element = NULL;
	info.first_element = &element;
	va_start(args, format);
	info.args = &args;
	info.function = ft_printfunction;
	info.total_len = 1;
	info.data = 0;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	return ((int)info.total_len);
}
