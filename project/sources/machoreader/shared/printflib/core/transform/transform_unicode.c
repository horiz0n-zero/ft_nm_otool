/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:16:52 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 11:20:10 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void					transform_unicode(t_printdata *data, char *dst)
{
	char				*unicode;

	unicode = (void*)&data->data;
	while (data->lenght-- > 0)
		*dst++ = *unicode++;
}
