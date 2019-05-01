/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_objc_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:31:08 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/01 17:40:39 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objective_c.h"

void		swap_list_header(struct s_objc_list_header *const o)
{
	o->entsize = __builtin_bswap32(o->entsize);
	o->count = __builtin_bswap32(o->count);
}

void		swap_image_info(struct s_objc_image_info *const o)
{
	o->version = __builtin_bswap32(o->version);
	o->flags = __builtin_bswap32(o->flags);
}

void		swap_class(struct s_objc_class *const o)
{
	o->isa = __builtin_bswap64(o->isa);
	o->superclass = __builtin_bswap64(o->superclass);
	o->cache = __builtin_bswap64(o->cache);
	o->vtable = __builtin_bswap64(o->vtable);
	o->data = __builtin_bswap64(o->data);
	o->reserved1 = __builtin_bswap64(o->reserved1);
	o->reserved2 = __builtin_bswap64(o->reserved2);
	o->reserved3 = __builtin_bswap64(o->reserved3);
}

void		swap_class_ro(struct s_objc_class_ro *const o)
{
	o->flags = __builtin_bswap32(o->flags);
	o->instance_start = __builtin_bswap32(o->instance_start);
	o->instance_size = __builtin_bswap32(o->instance_size);
	o->reserved = __builtin_bswap32(o->reserved);
	o->ivar_layout = __builtin_bswap64(o->ivar_layout);
	o->name = __builtin_bswap64(o->name);
	o->base_methods = __builtin_bswap64(o->base_methods);
	o->base_protocols = __builtin_bswap64(o->base_protocols);
	o->ivars = __builtin_bswap64(o->ivars);
	o->weak_ivar_layout = __builtin_bswap64(o->weak_ivar_layout);
	o->base_properties = __builtin_bswap64(o->base_properties);
}

void		swap_method(struct s_objc_method *const o)
{
	o->name = __builtin_bswap64(o->name);
	o->types = __builtin_bswap64(o->types);
	o->imp = __builtin_bswap64(o->imp);
}
