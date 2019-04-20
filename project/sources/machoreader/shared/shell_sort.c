/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 12:44:34 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 12:54:48 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

void			shell_sort(
		void **const array,
		const int count,
		int (*const func)(void *const a, void *const b))
{
	int			i;
	int			j;
	int			space;
	void		*tmp;

	space = count / 2;
	i = 0;
	j = space;
	while (j > 0)
	{
		while (j < count)
		{
			if (func(*(array + i), *(array + j)))
			{
				tmp = *(array + i);
				*(array + i) = *(array + j);
				*(array + j) = tmp;
			}
			++i;
			++j;
		}
		i = 0;
		j = --space;
	}
}
