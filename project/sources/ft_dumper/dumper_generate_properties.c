/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_properties.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:10:04 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/08 15:32:48 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

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
		type = get_primitive_type(dumper, attributes, &attributes);
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
