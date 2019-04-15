/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:59:25 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/14 15:09:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

int					ft_atoi(const char *src)
{
	int				n;
	int				length;

	while (*src == ' ')
		src++;
	length = 0;
	n = 0;
	while (src[length] && src[length] >= '0' && src[length] <= '9')
		length++;
	//src += length;
	while (length)
	{
		n = n * 10 + (int)(*src++ - '0');
		--length;
	}
	return (n);
}
