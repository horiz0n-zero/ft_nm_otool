/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_static_lib.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:31:55 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/12 17:39:36 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

static void				*check_static_lib_longname(struct s_macho_binary *const binary)
{
	if (!GETO(binary, binary->position, SYMDEF_64_SORTED))
		return (set_error_nil(binary, "size < SYMDEF max"));
	if (!ft_strcmp(binary->position, SYMDEF))
		printf("SYMDEF");
	else if (!ft_strcmp(binary->position, SYMDEF_SORTED))
		printf("SYMDEF S");
	else if (!ft_strcmp(binary->position, SYMDEF_64))
		printf("SYMDEF 64");
	else if (!ft_strcmp(binary->position, SYMDEF_64_SORTED))
		printf("SYMDEF 64 S");
	else
		return (binary);
}

void					read_static_lib(struct s_macho_binary *const binary,
		struct s_macho *const macho)
{
	struct ar_hdr		*header;

	if (!(header = GETSETO(binary, &binary->position, struct ar_hdr)))
		return (set_error(binary, "size < struct ar_hdr"));
	while ((GETSET(binary, &binary->position, 1)) && *(char*)binary->position == ' ')
		continue ;
	if (!GETO(binary, binary->position, ARFMAG) || ft_strncmp(binary->position, ARFMAG, sizeof(ARFMAG) - 1))
		return (set_error(binary, "size < ar_fmag"));
	SET(binary, sizeof(ARFMAG) - 1);
	printf("%s\n", binary->position);
	if (!(check_static_lib_longname(binary)))
		return ;
}
