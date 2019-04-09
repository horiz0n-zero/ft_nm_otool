/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unget_macho_binary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:23:22 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/09 14:49:52 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

void						unget_macho_binary(struct s_macho_binary *const binary)
{
	if (binary)
	{
		if (binary->content && binary->content != MAP_FAILED)
			munmap((void*)binary->content, binary->content_size);
		// for each macho in 0..<count
		free(binary);
	}
}
