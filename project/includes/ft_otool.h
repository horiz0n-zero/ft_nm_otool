/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:44:30 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/29 15:41:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "machoreader.h"

struct						s_otool
{
	int						flags;
# define OTOOL_P 1 << 0
# define OTOOL_S 1 << 1
# define OTOOL_D 1 << 2

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

#endif
