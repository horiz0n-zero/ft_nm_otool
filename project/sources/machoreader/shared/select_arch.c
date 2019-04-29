/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:26:29 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 12:40:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

int								select_arch(
		struct s_macho_binary *const binary,
		int *const select)
{
	static const cpu_type_t		cpu = CPU_TYPE_X86_64;
	int							index;

	*select = 0;
	if (binary->count <= 1)
		return (0);
	index = 0;
	while (index < binary->count)
	{
		if (binary->macho[index].statics)
		{
			if (binary->macho[index].statics->macho->header->cputype == cpu)
			{
				*select = 1;
				return (index);
			}
		}
		else if (binary->macho[index].header->cputype == cpu)
		{
			*select = 1;
			return (index);
		}
		++index;
	}
	return (0);
}
