/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:20:18 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/09 13:54:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static char				*generate_methods_params(
		struct s_dumper *const dumper,
		char *name, char *types, char *ptr)
{
	int					isarray;

	isarray = 0;
	while (*name)
	{
		if (*name == ':' && *types)
		{
			*ptr++ = ':';
			*ptr++ = '(';
			ptr = str_push(get_primitive_instance_type(dumper, types, &isarray), ptr);
			while (*types && !(*types >= '0' && *types <= '9'))
				++types;
			while (*types >= '0' && *types <= '9')
				++types;
			if (isarray && !(isarray = 0))
				*ptr++ = '*';
			*ptr++ = ')';
			name++;
		}
		else
			*ptr++ = *name++;
	}
	return (ptr);
}

static const char		*generate_methods_types(
		struct s_dumper *const dumper,
		struct s_method *const method,
		char *types)
{
	static char			buffer[2048];
	char				*ptr;
	int					isarray;

	ptr = buffer;
	isarray = 0;
	*ptr++ = '(';
	ptr = str_push(get_primitive_instance_type(dumper, types, &isarray), ptr);
	if (*(ptr - 1) == '(')
		ptr = str_push("void", ptr);
	while (*types && *types != ':')
		++types;
	if (*types == ':' && *++types == '8')
		++types;
	if (isarray)
		*ptr++ = '*';
	*ptr++ = ')';
	*ptr++ = ' ';
	ptr = generate_methods_params(dumper, method->name, types, ptr);
	*ptr = 0;
	return (buffer);
}

void					dumper_generate_methods(
		struct s_dumper *const dumper,
		struct s_method *methods, int count,
		const int isclass, const char *const prefix)
{
	if (isclass)
	{
		while (count--)
		{
			ft_fprintf(dumper->fdoutput, "%s+%s;\n", prefix,
					generate_methods_types(dumper, methods, methods->types));
			methods++;
		}
	}
	else
	{
		while (count--)
		{
			ft_fprintf(dumper->fdoutput, "%s-%s;\n", prefix,
					generate_methods_types(dumper, methods, methods->types));
			methods++;
		}
	}
}











