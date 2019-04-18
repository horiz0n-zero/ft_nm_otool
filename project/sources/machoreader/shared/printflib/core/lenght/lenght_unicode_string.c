/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_unicode_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:05:42 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 11:05:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void					lenght_unicode_string(t_printdata *data, va_list *args)
{
	wchar_t				*ptr;

	ptr = va_arg(*args, wchar_t*);
	if (!ptr)
	{
		ptr = (void*)"(null)";
		data->len = sizeof("(null)");
		data->data = (int64_t)ptr;
	}
	else
	{
		data->data = (int64_t)ptr;
		while (*ptr)
		{
			if (*ptr < 0x80)
				data->len++;
			else if (*ptr < 0x0800)
				data->len += 2;
			else if (*ptr < 0x010000)
				data->len += 3;
			else
				data->len += 4;
			ptr++;
		}
	}
}
