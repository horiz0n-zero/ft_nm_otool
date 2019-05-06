/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_strjoins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:24:11 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/06 13:33:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

char			*static_strjoins(int count, ...)
{
	static char	buffer[2048];
	char		*ptr;
	char		*source;
	va_list		args;

	va_start(args, count);
	ptr = buffer;
	while (count--)
	{
		source = va_arg(args, char*);
		while (*source)
			*ptr++ = *source++;
	}
	*ptr = 0;
	va_end(args);
	return (buffer);
}
