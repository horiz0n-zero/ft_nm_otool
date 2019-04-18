/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:15:03 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 11:15:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void			pointer_push(uint64_t value, char *dst)
{
	if (!value)
	{
		*dst = '0';
		return ;
	}
	while (value)
	{
		*dst-- = "0123456789abcdef"[value % 16];
		value /= 16;
	}
}

void				transform_pointer(t_printdata *data, char *dst)
{
	if (data->flags & MINUS)
	{
		*dst++ = '0';
		*dst++ = 'x';
		while (data->precision-- > 0)
			*dst++ = '0';
		pointer_push((uint64_t)data->data, (dst += data->lenght) - 1);
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 0)
			*dst++ = ' ';
		*dst++ = '0';
		*dst++ = 'x';
		while (data->precision-- > 0)
			*dst++ = '0';
		pointer_push((uint64_t)data->data, (dst += data->lenght) - 1);
	}
}
