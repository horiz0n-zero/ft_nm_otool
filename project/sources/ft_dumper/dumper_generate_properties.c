/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_properties.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:10:04 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/08 14:14:07 by afeuerst         ###   ########.fr       */
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
			return (attributes);
		if (*attributes == '?')
			return (attributes + 1);
		if (*attributes == '@' && *++attributes == '\"')
		{
			while (*++attributes && *attributes != '\"')
				*ptr++ = *attributes;
			*src = ++attributes;
		}
		else
			return ("id");
	}
	*ptr = 0;
	return (buffer);
}

static const char				*g_properties[256] =
{
	['R'] = "readonly",
	['C'] = "copy",
	['&'] = "retain",
	['N'] = "nonatomic",
	['D'] = "dynamic",
	['W'] = "weak"
};

static char						*properties_getter_setter(
		char *attributes, char *ptr)
{
	char						*src;

	if (*attributes++ == 'G')
		src = "getter";
	else
		src = "setter";
	while (*src)
		*ptr++ = *src++;
	*ptr++ = '=';
	while (*attributes && *attributes != ',')
		*ptr++ = *attributes++;
	return (ptr);
}

static char						*properties_get_properties(
		char *attributes)
{
	static char					buffer[2048];
	char						*ptr;
	const char					*src;

	ptr = buffer;
	while (*attributes)
	{
		src = g_properties[(int)*attributes];
		if (src && ++attributes)
			while (*src)
				*ptr++ = *src++;
		else if (*attributes == 'G' || *attributes == 'S')
			ptr = properties_getter_setter(attributes, ptr);
		if (*attributes++ == ',' && *attributes != 'V' && (*ptr++ = ','))
			*ptr++ = ' ';
		else
			break ;
	}
	*ptr = 0;
	return (buffer);
}

void							dumper_generate_properties(
		struct s_dumper *const dumper,
		struct s_property *properties, int count,
		const char *const prefix)
{
	const char					*type;
	char						*attributes;

	while (count--)
	{
		attributes = properties->attributes;
		type = properties_get_type(dumper, &attributes);
		if (!type)
			type = properties_get_extratype(dumper, &attributes);
		if (*attributes++ == ',' && *attributes != 'V') // id
			ft_fprintf(dumper->fdoutput, "%s@property(%s) %s %s;\n",
				prefix, properties_get_properties(attributes),
				type, properties->name);
		else
			ft_fprintf(dumper->fdoutput, "%s@property %s %s;\n", prefix,
				type, properties->name);
		properties++;
	}
	write(dumper->fdoutput, "\n", 1);
}
