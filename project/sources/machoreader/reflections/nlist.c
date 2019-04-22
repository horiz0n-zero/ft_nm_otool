/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:18:23 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/22 16:05:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static char			*get_nlist_type(
		struct s_symbol *const symbol,
		char *ptr,
		const uint8_t type)
{
	if (type == N_PBUD)
	{
		if (type == N_UNDF && symbol->value)
			ptr = str_push("(common) ", ptr);
		else
		{
			if (type == N_PBUD)
				ptr = str_push("(prebound ", ptr);
			else
				ptr = str_push("(", ptr);
			if ((symbol->desc & REFERENCE_TYPE) == REFERENCE_FLAG_UNDEFINED_LAZY)
				ptr = str_push("undefined [lazy bound]) ", ptr);
			else if ((symbol->desc & REFERENCE_TYPE) == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
				ptr = str_push("undefined [private lazy bound]) ", ptr);
			else if ((symbol->desc & REFERENCE_TYPE) == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
				ptr = str_push("undefined [private]) ", ptr);
			else
				ptr = str_push("undefined) ", ptr);
		}
	}
	else if (type == N_ABS)
		ptr = str_push("(absolute) ", ptr);
	else if (type ==  N_INDR)
		ptr = str_push("(indirect) ", ptr);
	else if (type ==  N_SECT)
	{
		if (symbol->section)
		{
			ptr = str_push("(", ptr);
			ptr = str_push(symbol->section->segname, ptr);
			*ptr++ = ',';
			ptr = str_push(symbol->section->sectname, ptr);
			ptr = str_push(") ", ptr);
		}
		else
			ptr = str_push("(?,?) ", ptr);
	}
	else if (type != N_UNDF)
		ptr = str_push("(?) ", ptr);
	else
		ptr = str_push("(undefined) ", ptr);
	return (ptr);
}

const char			*get_nlist_ext(struct s_symbol *const symbol)
{
	static char		buffer[2048];
	char			*ptr;

	ptr = get_nlist_type(symbol, buffer, symbol->type & N_TYPE);
	if (symbol->type & N_EXT)
	{
		if (symbol->desc & REFERENCED_DYNAMICALLY)
			ptr = str_push("[referenced dynamically] ", ptr);
		if (symbol->type & N_PEXT)
		{
			if ((symbol->desc & N_WEAK_DEF) == N_WEAK_DEF)
				ptr = str_push("weak private external ", ptr);
			else
				ptr = str_push("private external ", ptr);
		}
		else
		{
			if ((symbol->desc & N_WEAK_REF) == N_WEAK_REF || (symbol->desc & N_WEAK_DEF) == N_WEAK_DEF)
				ptr = str_push("weak external ", ptr);
			else
				ptr = str_push("external ", ptr);
		}
	}
	else
	{
		if (symbol->type & N_PEXT)
			ptr = str_push("non-external (was a private external) ", ptr);
		else
			ptr = str_push("non-external ", ptr);
	}
	*ptr = 0;
	return (buffer);
}
