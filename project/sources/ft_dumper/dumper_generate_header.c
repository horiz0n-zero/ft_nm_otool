/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_header.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:09:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 16:47:36 by afeuerst         ###   ########.fr       */
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

static void				print_class(struct s_class *const c, const int index)
{
	struct s_method		*m;
	int					mindex;
	struct s_instance_var	*ivars;
	int						ivarsindex;
	struct s_property		*pr;
	int						prindex;

	if (index < 0)
		ft_printf(">--------------------> %s\n", c->name);
	else
		ft_printf("---------------------- [%d] %s\n", index, c->name);
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
	{
		mindex = 0;
		m = c->methods;
		while (mindex < c->methods_count)
		{
			ft_printf("%28s ---------------------\n", "");
			ft_printf("%28s - %016llx %s\n", "name", m->method->name, m->name);
			ft_printf("%28s - %016llx %s\n", "types", m->method->types, m->types);
			ft_printf("%28s - %016llx\n", "imp", m->method->imp);
			if (++mindex >= c->methods_count)
				ft_printf("%28s ---------------------\n", "");
			m++;
		}
	}
	if (c->instances)
	{
		ivarsindex = 0;
		ivars = c->instances;
		ft_printf("%28s instances { %d }\n", "", c->instances_count);
		while (ivarsindex < c->instances_count)
		{
			ft_printf("%28s %016llx\n", "offset", ivars->ivar->offset);
			ft_printf("%28s %016llx %s\n", "name", ivars->ivar->name, ivars->name);
			ft_printf("%28s %016llx %s\n", "type", ivars->ivar->type, ivars->type);
			ft_printf("%28s %08x\n", "alignment", ivars->ivar->alignment);
			ft_printf("%28s %08x\n", "size", ivars->ivar->size);
			if (++ivarsindex < c->instances_count)
				ft_printf("\n");
			ivars++;
		}
	}
	if (c->properties)
	{
		prindex = 0;
		pr = c->properties;
		ft_printf("%28s properties { %d }\n", "", c->properties_count);
		while (prindex < c->properties_count)
		{
			ft_printf("%28s %016llx %s\n", "name", pr->property->name, pr->name);
			ft_printf("%28s %016llx %s\n", "attributes", pr->property->attributes, pr->attributes);
			if (++prindex < c->properties_count)
				ft_printf("\n");
			pr++;
		}
	}
	if (c->superclass)
	{
		print_class(c->superclass, -1);
	}
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
		print_class(c, index);
		index++;
	}
}



