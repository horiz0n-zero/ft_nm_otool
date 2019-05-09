/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_primitive_instance_type.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:50:15 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/09 13:27:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static const struct s_type_desc		g_primitives_instances[256] =
{
	['c'] = {"char", "int8_t"},
	['C'] = {"unsigned char", "uint8_t"},
	['s'] = {"short", "int16_t"},
	['S'] = {"unsigned short", "uint16_t"},
	['i'] = {"int", "int32_t"},
	['I'] = {"unsigned int", "uint32_t"},
	['l'] = {"long", "int32_t"},
	['L'] = {"unsigned long", "uint32_t"},
	['q'] = {"long long", "int64_t"},
	['Q'] = {"unsigned long long", "uint64_t"},
	['f'] = {"float", "float"},
	['d'] = {"double", "double"},
	['B'] = {"_Bool", "_Bool"},
	['v'] = {"void", "void"},
	['*'] = {"char *", "int8_t *"},
	['#'] = {"Class", "Class"},
	[':'] = {"SEL", "SEL"},
	['?'] = {"?", "?"},
	['b'] = {"bitfield", "bitfield"}
};

char								*instance_type_id(const char *types, char *const buffer)
{
	char							*ptr;

	if (!*types || (*types >= '0' && *types <= '9'))
		return (str_push("id", buffer));
	ptr = buffer;
	if (*types++ == '\"')
	{
		if (*types == '<')
			ptr = str_push("id ", ptr);
		while (*types && *types != '\"')
			*ptr++ = *types++;
	}
	if (*ptr != '>' && *buffer != 'i')
		*ptr++ = '*';
	return (ptr);
}

char								*instance_extra(
		struct s_dumper *const dumper,
		char *types, char *ptr,
		int *const isarray)
{
	if (*types == '{' && ++types)
	{
		while (*types && *types != '=' && *types != '}')
			*ptr++ = *types++;
	}
	if (*types == '[')
	{
		*isarray = ft_atoi(++types);
		while (*types >= '0' && *types <= '9')
			++types;
		return ((char*)get_primitive_instance_type(dumper, types, isarray));
	}
	else if (*types == '(' && ++types)
	{
		while (*types && *types != '=' && *types != ')')
			*ptr++ = *types++;
	}
	return (ptr);
}

const char							*get_primitive_instance_type(
		struct s_dumper *const dumper,
		char *types, int *const isarray)
{
	const struct s_type_desc		*desc;
	static char						buffer[2048];
	char							*ptr;
	int								pointer_count;

	ptr = buffer;
	pointer_count = 0;
	while (*types == '^' && ++types)
		++pointer_count;
	if ((desc = g_primitives_instances + (int)*types)->type_bits)
	{
		if (dumper->flags & DUMPER_B)
			ptr = str_push(desc->type_bits, ptr);
		else
			ptr = str_push(desc->type_native, ptr);
	}
	else if (*types == '@')
		ptr = instance_type_id(++types, ptr);
	else
		ptr = instance_extra(dumper, types, ptr, isarray);
	while (pointer_count-- > 0)
		*ptr++ = '*';
	*ptr = 0;
	return (buffer);
}








