/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_get_sections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 10:18:58 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 11:37:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static inline void		dumper_get_proto_cat(
		struct s_macho *const macho,
		struct s_dumper *const dumper)
{
	dumper->proto_list = get_macho_section(macho, SEG_DATA, "__objc_protolist");
	if (!dumper->proto_list)
	{
		dumper->proto_list = get_macho_section(macho, "__OBJC2", "__protocol_list");
		if (!dumper->proto_list)
			dumper->proto_list = get_macho_section(macho, "__DATA_CONST", "__objc_protolist");
	}
	dumper->cat_list = get_macho_section(macho, SEG_DATA, "__objc_catlist");
	if (!dumper->cat_list)
	{
		dumper->cat_list = get_macho_section(macho, "__OBJC2", "__category_list");
		if (!dumper->cat_list)
			dumper->cat_list = get_macho_section(macho, "__DATA_CONST", "__objc_catlist");
	}
}

int						dumper_get_sections(
		struct s_macho *const macho,
		struct s_dumper *const dumper)
{
	dumper->class_list = get_macho_section(macho, SEG_DATA, "__objc_classlist");
	if (!dumper->class_list)
	{
		dumper->class_list = get_macho_section(macho, "__OBJC2", "__class_list");
		if (!dumper->class_list)
		{
			dumper->class_list = get_macho_section(macho, "__DATA_CONST", "__objc_classlist");
			if (!dumper->class_list)
				return (1);
		}
	}
	dumper_get_proto_cat(macho, dumper);
	dumper->encryption = get_macho_first_loadcommand(macho, LC_ENCRYPTION_INFO);
	if (!dumper->encryption)
		dumper->encryption = get_macho_first_loadcommand(macho, LC_ENCRYPTION_INFO_64);
	return (0);
}
