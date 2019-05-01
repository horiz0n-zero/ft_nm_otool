/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_objc_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:40:16 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/01 17:56:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objective_c.h"

void		swap_ivar(struct s_objc_ivar *const o)
{
	o->offset = __builtin_bswap64(o->offset);
	o->name = __builtin_bswap64(o->name);
	o->type = __builtin_bswap64(o->type);
	o->alignment = __builtin_bswap32(o->alignment);
	o->size = __builtin_bswap32(o->size);
}

void		swap_property(struct s_objc_property *const o)
{
	o->name = __builtin_bswap64(o->name);
	o->attributes = __builtin_bswap64(o->attributes);
}

void		swap_protocol(struct s_objc_protocol *const o)
{
	o->isa = __builtin_bswap64(o->isa);
	o->name = __builtin_bswap64(o->name);
	o->protocols = __builtin_bswap64(o->protocols);
	o->instance_methods = __builtin_bswap64(o->instance_methods);
	o->class_methods = __builtin_bswap64(o->class_methods);
	o->optional_instance_methods = __builtin_bswap64(o->optional_instance_methods);
	o->optional_class_methods = __builtin_bswap64(o->optional_class_methods);
	o->instance_properties = __builtin_bswap64(o->instance_properties);
	o->size = __builtin_bswap32(o->size);
	o->flags = __builtin_bswap32(o->flags);
	o->extended_method_types = __builtin_bswap64(o->extended_method_types);
}

void		swap_category(struct s_objc_category *const o)
{
	o->name = __builtin_bswap64(o->name);
	o->class = __builtin_bswap64(o->class);
	o->instance_methods = __builtin_bswap64(o->instance_methods);
	o->class_methods = __builtin_bswap64(o->class_methods);
	o->protocols = __builtin_bswap64(o->protocols);
	o->instance_properties = __builtin_bswap64(o->instance_properties);
	o->v7 = __builtin_bswap64(o->v7);
	o->v8 = __builtin_bswap64(o->v8);
}
