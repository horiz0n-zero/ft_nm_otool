/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:44:30 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 09:41:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "machoreader.h"

struct						s_otool
{
	int						flags;
# define OTOOL_P 1 << 0
# define OTOOL_H 1 << 1
# define OTOOL_M 1 << 2

	int						pad;
	char					*syntax;
	void					(*content32)(
			struct s_otool *const otool,
			struct s_macho_binary *const bin,
			struct s_macho *const macho,
			struct s_section *const section);
	void					(*content64)(
			struct s_otool *const otool,
			struct s_macho_binary *const bin,
			struct s_macho *const macho,
			struct s_section *const section);
};

void						otool_usage(void);

void						otool_process_files(
		struct s_otool *const otool,
		char **argv);

/*
** print text content
*/
void						otool_content_default_32(
		struct s_otool *const otool,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_section *const section);
void						otool_content_default_64(
		struct s_otool *const otool,
		struct s_macho_binary *const bin,
		struct s_macho *const macho,
		struct s_section *const section);
void						otool_private_header(
		struct s_otool *const otool,
		struct s_macho *const macho);
void						otool_headers(
		struct s_otool *const otool,
		struct s_macho *const macho);

struct						s_header
{
	uint32_t				cmd;
	uint32_t				pad;
	void					(*print)(struct s_loadcommand *const lc);
};
void						print_segment(struct s_loadcommand *const lc);
void						print_segment64(struct s_loadcommand *const lc);
void						print_fvmlib(struct s_loadcommand *const lc);
void						print_dylib(struct s_loadcommand *const lc);
void						print_subframework(struct s_loadcommand *const lc);
void						print_subclient(struct s_loadcommand *const lc);
void						print_subumbrella(struct s_loadcommand *const lc);
void						print_sublibrary(struct s_loadcommand *const lc);
void						print_prebound(struct s_loadcommand *const lc);
void						print_dylinker(struct s_loadcommand *const lc);
void						print_routines(struct s_loadcommand *const lc);
void						print_routines64(struct s_loadcommand *const lc);
void						print_symtab(struct s_loadcommand *const lc);
void						print_dysymtab(struct s_loadcommand *const lc);
void						print_two_level(struct s_loadcommand *const lc);
void						print_prebind(struct s_loadcommand *const lc);
void						print_uuid(struct s_loadcommand *const lc);
void						print_rpath(struct s_loadcommand *const lc);
void						print_linkedit(struct s_loadcommand *const lc);
void						print_encry(struct s_loadcommand *const lc);
void						print_min_version(struct s_loadcommand *const lc);
void						print_build_version(struct s_loadcommand *const lc);
void						print_dyld_info(struct s_loadcommand *const lc);
void						print_linker_option(struct s_loadcommand *const lc);
void						print_symseg(struct s_loadcommand *const lc);
void						print_fvmfile_command(struct s_loadcommand *const lc);
void						print_main(struct s_loadcommand *const lc);
void						print_source_version(struct s_loadcommand *const lc);

void						print_segment_sections32(struct s_segment *const segment);
void						print_segment_sections64(struct s_segment *const segment);

#endif
