/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:37:59 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/08 16:14:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

void						*ft_memalloc(size_t size)
{
	register char *const	ptr = malloc(size);

	if (!ptr)
		return (NULL);
	while (size)
		ptr[--size] = 0;
	return (ptr);
}
