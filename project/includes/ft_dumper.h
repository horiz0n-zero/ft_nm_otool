/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:03:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/01 16:32:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DUMPER_H
# define FT_DUMPER_H

# include "machoreader.h"
# include "objective_c.h"

struct								s_dumper
{
	int								flags;
# define DUMPER_O 1 << 0
# define DUMPER_S 1 << 1
# define DUMPER_U 1 << 2

	int								pad;

	char							*output;
	int								fdoutput;

	
};

void								dumper_show_lc_encryption(char **argv);
void								dumper_show_uuid(char **argv);

void								dumper_generate_header(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin);

#endif
