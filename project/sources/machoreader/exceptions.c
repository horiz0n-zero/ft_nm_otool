/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:11:30 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 14:19:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

inline void					*align_object(struct s_macho_binary *const binary,
		const size_t alignment)
{
	register char			*ptr;
	register char *const	end_ptr = ((char*)binary->content) + binary->content_size;

	if (alignment)
	{
		ptr = binary->position;
		while ((size_t)ptr % alignment)
			ptr++;
		if (ptr >= end_ptr)
			return (NULL);
		binary->position = ptr;
	}
	return (binary->position);
}

inline void					*setoffset_object(struct s_macho_binary *const binary, const size_t size)
{
	register char *const	end_ptr = ((char*)binary->content) + binary->content_size;
	register char *const	offset_ptr = ((char*)binary->content) + size;

	if (offset_ptr >= end_ptr)
		return (NULL);
	binary->position = offset_ptr;
	return (offset_ptr);
}

inline void					*offset_object(struct s_macho_binary *const binary, const size_t size)
{
	register char *const	end_ptr = ((char*)binary->content) + binary->content_size;
	register char *const	offset_ptr = ((char*)binary->content) + size;

	if (offset_ptr >= end_ptr)
		return (NULL);
	return (offset_ptr);
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
