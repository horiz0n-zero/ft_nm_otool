/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_primitive_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:14:43 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/09 11:15:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static struct s_type_desc		g_type_desc[256] =
{
	['c'] = {"char", "int8_t"},
	['C'] = {"unsigned char", "uint8_t"},
	['s'] = {"short", "int16_t"},
	['S'] = {"unsigned short", "uint16_t"},
	['i'] = {"int", "int32_t"},
	['I'] = {"unsigned int", "uint32_t"},
	['l'] = {"long", "int64_t"},
	['L'] = {"unsigned long", "uint64_t"},
	['q'] = {"long long", "int64_t"},
	['Q'] = {"unsigned long long", "uint64_t"},
	['f'] = {"float", "float"},
	['d'] = {"double", "double"},
	['D'] = {"long double", "long double"},
	['B'] = {"_Bool", "_Bool"},
	['v'] = {"void", "void"},
	['#'] = {"Class", "Class"},
	[':'] = {"SEL", "SEL"}
};

static char						*properties_get_structured_type(
		char *attributes,
		char *ptr,
		char **const src)
{
	while (*attributes && *attributes != '=')
		*ptr++ = *attributes++;
	while (*attributes && *attributes != '}' && *attributes != ')')
	{
		if (*attributes == '{' || *attributes == '(')
		{
			while (*attributes && *attributes != '}' && *attributes != ')')
				attributes++;
			if (*attributes)
				++attributes;
		}
		else
			++attributes;
	}
	if (*attributes)
		++attributes;
	*src = attributes;
	return (ptr);
}

static char						*properties_get_extratype(
		struct s_dumper *const dumper,
		char **const src)
{
	char						*ptr;
	static char					buffer[2048];
	char						*attributes;

	ptr = buffer;
	attributes = *src;
	if (*attributes == 'T' && ++attributes)
	{
		if (*attributes == '{' || *attributes == '(')
			ptr = properties_get_structured_type(++attributes, ptr, src);
		else if (*attributes == '?')
			ptr = str_push("???", ptr);
		else if (*attributes == '@' && *++attributes == '\"')
		{
			while (*++attributes && *attributes != '\"')
				*ptr++ = *attributes;
			*ptr++ = '*';
			*src = ++attributes;
		}
		else
			return ("id");
	}
	*ptr = 0;
	return (buffer);
}

static const char				*properties_get_type(
		struct s_dumper *const dumper,
		char **const attributes)
{
	char						*ptr;
	struct s_type_desc			*desc;

	ptr = *attributes;
	if (*ptr == 'T')
	{
		++ptr;
		if ((desc = g_type_desc + (int)*ptr)->type_bits)
		{
			*attributes = ++ptr;
			if (dumper->flags & DUMPER_B)
				return (desc->type_bits);
			else
				return (desc->type_native);
		}
	}
	return (NULL);
}

const char						*get_primitive_type(
		struct s_dumper *const dumper,
		char *attributes, char **const ptr)
{
	const char					*type;
	static char					buffer[2048];
	char						*str;

	type = properties_get_type(dumper, &attributes);
	if (!type)
		type = properties_get_extratype(dumper, &attributes);
	if (type && *type == '<')
	{
		str = str_push("id ", buffer);
		str = str_push(type, str);
		*str = 0;
		return (buffer);
	}
	if (ptr)
		*ptr = attributes;
	return (type);
}
