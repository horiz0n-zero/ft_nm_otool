/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:14:55 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/23 11:19:39 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

char			*number_push(int number, char *ptr)
{
	char		*save;
	int			n;

	if (number < 0)
	{
		number = -number;
		*ptr++ = '-';
	}
	n = number;
	while (n)
	{
		n /= 10;
		ptr++;
	}
	save = ptr;
	while (number)
	{
		*--ptr = (char)number % 10 + '0';
		number /= 10;
	}
	return (save);
}
