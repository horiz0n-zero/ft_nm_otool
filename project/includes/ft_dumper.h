/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:03:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/09 10:12:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DUMPER_H
# define FT_DUMPER_H

# include "machoreader.h"
# include "objective_c.h"

typedef struct s_protocol			t_protocol;
struct								s_protocol
{
	uint64_t						value;
	char							*name;
	struct s_objc_protocol			*protocol;

	struct s_method					*class_methods;
	int								class_methods_count;

	struct s_method					*instance_methods;
	int								instance_methods_count;

	struct s_method					*o_class_methods;
	int								o_class_methods_count;

	struct s_method					*o_instance_methods;
	int								o_instance_methods_count;

	struct s_instance_var			*instances;
	int								instances_count;

	struct s_property				*properties;
	int								properties_count;

	struct s_protocol				*protocols;
	int								protocols_count;
};

struct								s_property
{
	struct s_objc_property			*property;
	char							*name;
	char							*attributes;
};

struct								s_instance_var
{
	struct s_objc_ivar				*ivar;
	char							*name;
	char							*type;
};

struct								s_method
{
	struct s_objc_method			*method;
	char							*name;
	char							*types;
};

typedef struct s_class				t_class;
struct								s_class
{
	uint64_t						value;
	int								isswift;
	int								pad;
	char							*name;
	struct s_objc_class				*class;
	struct s_objc_class_ro			*ro;

	struct s_method					*methods;
	int								methods_count;

	struct s_instance_var			*instances;
	int								instances_count;

	struct s_property				*properties;
	int								properties_count;

	struct s_protocol				*protocols;
	int								protocols_count;

	struct s_class					*superclass;
	char							*superclass_name;
	struct s_class					*metaclass;
};

struct								s_category
{
	uint64_t						value;
	char							*name;
	struct s_objc_category			*category;

	struct s_method					*instance_methods;
	int								instance_methods_count;

	struct s_method					*class_methods;
	int								class_methods_count;

	struct s_protocol				*protocols;
	int								protocols_count;

	struct s_property				*properties;
	int								properties_count;
};

typedef struct s_type				t_type;
struct								s_dumper
{
	int								flags;
# define DUMPER_O 1 << 0
# define DUMPER_S 1 << 1
# define DUMPER_U 1 << 2
# define DUMPER_F 1 << 3
# define DUMPER_B 1 << 4

	int								fdoutput;
	char							*output;

	struct s_loadcommand			*encryption;

	struct s_section				*class_list;
	struct s_section				*proto_list;
	struct s_section				*cat_list;

	struct s_class					*class;
	int								class_count;

	struct s_protocol				*protocols;
	int								protocols_count;

	struct s_category				*categories;
	int								categories_count;
};

void								dumper_show_lc_encryption(char **argv);
void								dumper_show_uuid(char **argv);

int									dumper_get_sections(
		struct s_macho *const macho,
		struct s_dumper *const dumper);
void								dumper_read_class(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho);
void								dumper_read_protocols(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho);
void								read_protocols(
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		const uint64_t value,
		struct s_protocol **const protocols, int *const protocols_count);
void								dumper_read_methods(
		struct s_macho *const macho, const uint64_t value,
		struct s_method **const methods, int *const count);
void								dumper_read_instances(
		struct s_macho *const macho,
		const uint64_t value,
		struct s_instance_var **const ivars, int *const count);
void								dumper_read_properties(
		struct s_macho *const macho,
		const uint64_t value,
		struct s_property **const properties, int *const count);
void								dumper_read_categories(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin,
		struct s_macho *const macho);

char								*section_addr_name(
		struct s_macho *const macho,
		const uint64_t value);
void								*section_addr_offset(
		struct s_macho *const macho,
		struct s_section *const section,
		const uint64_t value);
struct s_section					*section_addr_location(
		struct s_macho *const macho,
		const uint64_t value);

void								dumper_generate_header(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin);
void								dumper_generate_protocols(struct s_dumper *const dumper);
void								dumper_generate_class(struct s_dumper *const dumper);

char								*protocols_list(struct s_protocol *protocols, int count);
void								dumper_generate_methods(struct s_dumper *const dumper,
		struct s_method *methods, int count,
		const int isclass, const char *const prefix);
void								dumper_generate_instances(
		struct s_dumper *const dumper,
		struct s_instance_var *ivars, int count,
		const char *const prefix);
void								dumper_generate_properties(
		struct s_dumper *const dumper,
		struct s_property *properties, int count,
		const char *const prefix);

// debug
void								dumper_fatal(const char *const error);
void								dumper_debug_print(struct s_dumper *const dumper);

struct								s_type_desc
{
	const char						*type_native;
	const char						*type_bits;
};

const char							*get_primitive_type(
		struct s_dumper *const dumper,
		char *attributes, char **const ptr);
const char							*get_primitive_instance_type(
		struct s_dumper *const dumper,
		char *types, int *const isarray);

#endif
