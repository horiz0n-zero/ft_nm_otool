/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:50:26 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/12 15:55:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

int						ft_strncmp(const void *const p1, const void *const p2, int length)
{
	register const char	*s1;
	register const char	*s2;

	s1 = p1;
	s2 = p2;
	while (*s1 && *s2 && *s1 == *s2 && length)
	{
		s1++;
		s2++;
		length--;
	}
	return (length);
}
