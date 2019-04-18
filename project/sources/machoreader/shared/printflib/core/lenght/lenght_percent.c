/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:03:07 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 11:03:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void					lenght_percent(t_printdata *data, va_list *args)
{
	data->data = ((int64_t)va_arg(*args, int)) & 0xFF;
	if (data->width)
		data->len = data->width;
	else
		data->len = 1;
}
