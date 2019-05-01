/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objective_c.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 16:22:56 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/01 18:03:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTIVE_C_H
# define OBJECTIVE_C_H

# include <stdint.h>
# include <unistd.h>

struct			s_objc_list_header
{
	uint32_t	entsize;
	uint32_t	count;
};
void			swap_list_header(struct s_objc_list_header *const o);

struct			s_objc_image_info
{
	uint32_t	version;
	uint32_t	flags;
};
void			swap_image_info(struct s_objc_image_info *const o);

struct			s_objc_class
{
	uint64_t	isa;
	uint64_t	superclass;
	uint64_t	cache;
	uint64_t	vtable;
	uint64_t	data;
	uint64_t	reserved1;
	uint64_t	reserved2;
	uint64_t	reserved3;
};
void			swap_class(struct s_objc_class *const o);

struct			s_objc_class_ro
{
	uint32_t	flags;
	uint32_t	instance_start;
	uint32_t	instance_size;
	uint32_t	reserved;
	uint64_t	ivar_layout;
	uint64_t	name;
	uint64_t	base_methods;
	uint64_t	base_protocols;
	uint64_t	ivars;
	uint64_t	weak_ivar_layout;
	uint64_t	base_properties;
};
void			swap_class_ro(struct s_objc_class_ro *const o);

struct			s_objc_method
{
	uint64_t	name;
	uint64_t	types;
	uint64_t	imp;
};
void			swap_method(struct s_objc_method *const o);

struct			s_objc_ivar
{
	uint64_t	offset;
	uint64_t	name;
	uint64_t	type;
	uint32_t	alignment;
	uint32_t	size;
};
void			swap_ivar(struct s_objc_ivar *const o);

struct			s_objc_property
{
	uint64_t	name;
	uint64_t	attributes;
};
void			swap_property(struct s_objc_property *const o);

struct			s_objc_protocol
{
	uint64_t	isa;
	uint64_t	name;
	uint64_t	protocols;
	uint64_t	instance_methods;
	uint64_t	class_methods;
	uint64_t	optional_instance_methods;
	uint64_t	optional_class_methods;
	uint64_t	instance_properties;
	uint32_t	size;
	uint32_t	flags;
	uint64_t	extended_method_types;
};
void			swap_protocol(struct s_objc_protocol *const o);

struct			s_objc_category
{
	uint64_t	name;
	uint64_t	class;
	uint64_t	instance_methods;
	uint64_t	class_methods;
	uint64_t	protocols;
	uint64_t	instance_properties;
	uint64_t	v7;
	uint64_t	v8;
};
void			swap_category(struct s_objc_category *const o);

/*
*** masks for objc_image_info.flags
*/
# define OBJC_IMAGE_IS_REPLACEMENT 1 << 0
# define OBJC_IMAGE_SUPPORTS_GC    1 << 1

/*
*** Values for class_ro_t->flags
*/
# define RO_META               1 << 0
# define RO_ROOT               1 << 1
# define RO_HAS_CXX_STRUCTORS  1 << 2

#endif
