/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:14:29 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 11:14:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void		push_octal(uint64_t value, char *dst)
{
	if (!value)
		*dst = '0';
	while (value)
	{
		*dst-- = value % 8 + 48;
		value /= 8;
	}
}

void			transform_octal(t_printdata *data, char *dst)
{
	const char	pad = !data->precision && data->flags & ZERO ? '0' : ' ';

	if (data->flags & MINUS)
	{
		if (data->flags & HASH)
			*dst++ = '0';
		while (data->precision-- > 0)
			*dst++ = '0';
		push_octal((uint64_t)data->data, (dst += data->lenght) - 1);
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 0)
			*dst++ = pad;
		while (data->precision-- > 0)
			*dst++ = '0';
		if (data->flags & HASH)
			*dst++ = '0';
		push_octal((uint64_t)data->data, (dst += data->lenght) - 1);
	}
}
