/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:11:30 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 14:59:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

inline void					*align_object(struct s_macho_binary *const binary,
		const size_t alignment)
{
	register char			*ptr;
	register char *const	end_ptr = ((char*)binary->content) + binary->content_size;

	printf("align : %p - %p\nsize : %zd, alignement : %zd\n", binary->content, end_ptr, binary->content_size, alignment);
	if (alignment)
	{
		ptr = binary->position;
		while ((size_t)ptr % alignment)
			ptr++;
		if (ptr >= end_ptr)
			return (set_error_nil(binary, "size < required alignment"));
		binary->position = ptr;
	}
	return (binary->position);
}

void						*set_error_nil(struct s_macho_binary *const binary,
		const char *const error)
{
	binary->error = error;
	return (NULL);
}

void						set_error(struct s_macho_binary *const binary,
		const char *const error)
{
	binary->error = error;
}
