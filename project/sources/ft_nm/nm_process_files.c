/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:12:26 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/22 16:43:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static inline void			nm_process_files_default(
		struct s_nm *const nm,
		const char *const file)
{
	struct s_macho_binary	*bin;

	bin = get_macho_binary(file);
	if (bin->error)
		return (nm_process_error(bin));
	nm_process_file(nm, bin);
	unget_macho_binary(bin);
}

void						nm_process_files(
		struct s_nm *const nm,
		char **argv)
{
	int						multi;
	struct s_macho_binary	*bin;

	if (!*argv)
		nm_process_files_default(nm, DEFAULT_BIN);
	else
	{
		multi = (*argv && *(argv + 1)) ? 1 : 0;
		while (*argv)
		{
			bin = get_macho_binary(*argv++);
			if (bin->error)
			{
				nm_process_error(bin);
				continue ;
			}
			if (multi && bin->count > 0 && !bin->macho->statics)
				ft_printf("\n%s:\n", bin->file);
			nm_process_file(nm, bin);
			unget_macho_binary(bin);
		}
	}
}
