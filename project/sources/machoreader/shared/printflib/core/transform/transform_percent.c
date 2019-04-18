/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:14:50 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 11:14:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void				transform_percent(t_printdata *data, char *dst)
{
	const char		pad = data->flags & ZERO ? '0' : ' ';

	if (data->flags & MINUS)
	{
		*dst++ = '%';
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 1)
			*dst++ = pad;
		*dst = '%';
	}
}
