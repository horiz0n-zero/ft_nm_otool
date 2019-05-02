/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:03:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/02 12:33:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DUMPER_H
# define FT_DUMPER_H

# include "machoreader.h"
# include "objective_c.h"

struct								s_class
{
	uint64_t						value;
	int								isswift;
	int								pad;
	struct s_objc_class				*class;
	struct s_objc_class_ro			*ro;
};

struct								s_dumper
{
	int								flags;
# define DUMPER_O 1 << 0
# define DUMPER_S 1 << 1
# define DUMPER_U 1 << 2

	int								fdoutput;
	char							*output;

	struct s_section				*class_list;
	struct s_section				*proto_list;
	struct s_section				*cat_list;

	struct s_class					*class;
	int								class_count;
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


void								dumper_generate_header(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin);


#endif
