/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_prot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 10:05:08 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 10:05:10 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

const char			*get_vm_prot(const vm_prot_t prot)
{
	static char		buffer[4] = {'-', '-', '-', 0};

	if (prot & PROT_READ)
		buffer[0] = 'r';
	else
		buffer[0] = '-';
	if (prot & PROT_WRITE)
		buffer[1] = 'w';
	else
		buffer[1] = '-';
	if (prot & PROT_EXEC)
		buffer[2] = 'x';
	else
		buffer[2] = '-';
	return (buffer);
}
