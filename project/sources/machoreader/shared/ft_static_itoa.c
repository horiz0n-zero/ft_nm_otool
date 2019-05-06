/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:11:23 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/06 13:24:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

static int				static_itoa_count(int number)
{
	int					i;

	i = 0;
	while (number)
	{
		number /= 10;
		i++;
	}
	return (i);
}

char					*ft_static_itoa(int number)
{
	static char	buffer[64];
	char		*ptr;

	ptr = buffer;
	if (number < 0 && (*ptr++ = '-'))
		number = -number;
	if (number == 0)
		*ptr++ = '0';
	else
		ptr += static_itoa_count(number);
	*ptr = 0;
	while (number)
	{
		*--ptr = (char)(number % 10) + '0';
		number /= 10;
	}
	return (buffer);
}
