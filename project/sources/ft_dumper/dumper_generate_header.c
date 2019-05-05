/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_header.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:09:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/05 16:47:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"
#include <time.h>

static inline void		dumper_generate_header_print_date(const int fd)
{
	time_t				now;
	struct tm			*local;

	time(&now);
	local = localtime(&now);
	ft_fprintf(fd, "%0.2d/%0.2d/%0.2d %0.2d:%0.2d:%0.2d\n",
			local->tm_mday,
			local->tm_mon + 1,
			local->tm_year + 1900,
			local->tm_hour,
			local->tm_min,
			local->tm_sec);
}

static void				_print_instances(struct s_instance_var *ivars, const int count)
{
	int					ivarsindex;

	ivarsindex = 0;
	ft_printf("%28s instances { %d }\n", "", count);
	while (ivarsindex < count)
	{
		ft_printf("%28s %016llx\n", "offset", ivars->ivar->offset);
		ft_printf("%28s %016llx %s\n", "name", ivars->ivar->name, ivars->name);
		ft_printf("%28s %016llx %s\n", "type", ivars->ivar->type, ivars->type);
		ft_printf("%28s %08x\n", "alignment", ivars->ivar->alignment);
		ft_printf("%28s %08x\n", "size", ivars->ivar->size);
		if (++ivarsindex < count)
			ft_printf("\n");
		ivars++;
	}
}

static void				_print_method(struct s_method *m, const int count)
{
	int					mindex;

	mindex = 0;
	while (mindex < count)
	{
		ft_printf("%28s ---------------------\n", "");
		ft_printf("%28s - %016llx %s\n", "name", m->method->name, m->name);
		ft_printf("%28s - %016llx %s\n", "types", m->method->types, m->types);
		ft_printf("%28s - %016llx\n", "imp", m->method->imp);
		if (++mindex >= count)
			ft_printf("%28s ---------------------\n", "");
		m++;
	}
}

static void				_print_properties(struct s_property *pr, const int count)
{
	int						prindex;

	prindex = 0;
	ft_printf("%28s properties { %d }\n", "", count);
	while (prindex < count)
	{
		ft_printf("%28s %016llx %s\n", "name", pr->property->name, pr->name);
		ft_printf("%28s %016llx %s\n", "attributes", pr->property->attributes, pr->attributes);
		if (++prindex < count)
			ft_printf("\n");
		pr++;
	}
}

static void				print_protocol(struct s_protocol *const p, const int index, const char *const parent)
{
	if (parent)
		ft_printf("############################ [%d] %s(%s)\n", index, p->name, parent);
	else
		ft_printf("############################ [%d] %s\n", index, p->name);
	ft_printf("%22s %016llx\n", "isa", p->protocol->isa);
	ft_printf("%22s %016llx\n", "protocols", p->protocol->protocols);
	ft_printf("%22s %016llx\n", "instance_methods", p->protocol->instance_methods);
	_print_method(p->instance_methods, p->instance_methods_count);
	ft_printf("%22s %016llx\n", "class_methods", p->protocol->class_methods);
	_print_method(p->class_methods, p->class_methods_count);
	ft_printf("%22s %016llx\n", "optional_insta_methods", p->protocol->optional_instance_methods);
	_print_method(p->o_instance_methods, p->o_instance_methods_count);
	ft_printf("%22s %016llx\n", "optional_class_methods", p->protocol->optional_class_methods);
	_print_method(p->o_class_methods, p->o_class_methods_count);
	ft_printf("%22s %016llx\n", "instance_properties", p->protocol->instance_properties);
	if (p->properties_count)
		_print_properties(p->properties, p->properties_count);
	ft_printf("%22s %08x\n", "size", p->protocol->size);
	ft_printf("%22s %08x\n", "flags", p->protocol->flags);
	ft_printf("%22s %016llx\n", "extended_method_types", p->protocol->extended_method_types);
	if (p->protocols_count)
	{
		int				i = 0;

		while (i < p->protocols_count)
		{
			print_protocol(p->protocols + i, index * 100 + i, p->name);
			i++;
		}
	}
}

static void				print_class(struct s_class *const c, const int index, const char *const parent)
{
	if (index == -1)
		ft_printf("SUPERCLASS     >-------> %s: %s\n", parent, c->name);
	else if (index == -2)
		ft_printf("METACLASS      >-------> %s meta %s\n", parent, c->name);
	else
	{
		ft_printf("---------------------- [%d] %s\n", index, c->name);
	}
	ft_printf("%22s %s\n", "is Swift", c->isswift ? "true" : "false");
	ft_printf("%22s %016llx\n", "value", c->value);
	ft_printf("%22s %016llx\n", "isa", c->class->isa);
	ft_printf("%22s %016llx\n", "superclass", c->class->superclass);
	ft_printf("%22s %016llx\n", "cache", c->class->cache);
	ft_printf("%22s %016llx\n", "vtable", c->class->vtable);
	ft_printf("%22s %016llx\n", "data", c->class->data);
	if (c->class->data)
	{
		ft_printf("%22s %08x\n", "flags", c->ro->flags);
		ft_printf("%22s %08x\n", "instance_start", c->ro->instance_start);
		ft_printf("%22s %08x\n", "instance_size", c->ro->instance_size);
		ft_printf("%22s %08x\n", "reserved", c->ro->reserved);
		ft_printf("%22s %016llx\n", "ivar_layout", c->ro->ivar_layout);
		ft_printf("%22s %016llx\n", "name", c->ro->name);
		ft_printf("%22s %016llx\n", "base_methods", c->ro->base_methods);
		ft_printf("%22s %016llx\n", "base_protocols", c->ro->base_protocols);
		ft_printf("%22s %016llx\n", "ivars", c->ro->ivars);
		ft_printf("%22s %016llx\n", "weak_ivar_layout", c->ro->weak_ivar_layout);
		ft_printf("%22s %016llx\n", "base_properties", c->ro->base_properties);
	}
	if (c->methods)
		_print_method(c->methods, c->methods_count);
	if (c->instances)
		_print_instances(c->instances, c->instances_count);
	if (c->properties)
		_print_properties(c->properties, c->properties_count);
	if (c->superclass)
		print_class(c->superclass, -1, c->name);
	if (c->metaclass)
		print_class(c->metaclass, -2, c->name);
}

void					dumper_generate_header(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin)
{
	int					index;
	struct s_class		*c;

	ft_fprintf(dumper->fdoutput, "/*\n");
	ft_fprintf(dumper->fdoutput, " *\n");
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " * * ft_dumper Copyright (C) Antoine Feuerstein\n");
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " * * image source: %s\n", bin->file);
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " * * header generated at ");
	dumper_generate_header_print_date(dumper->fdoutput);
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " *\n");
	ft_fprintf(dumper->fdoutput, "*/\n\n");

	index = 0;
	while (index < dumper->class_count)
	{
		c = dumper->class + index;
		print_class(c, index, NULL);
		index++;
	}
	index = 0;
	while (index < dumper->protocols_count)
	{
		print_protocol(dumper->protocols + index, index, NULL);
		index++;
	}
}



