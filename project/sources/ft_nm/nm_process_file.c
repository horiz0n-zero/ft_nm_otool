/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:02:59 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 16:11:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void									nm_process_file(
		struct s_nm *const nm,
		const char *const file)
{
	struct s_macho_binary *const		bin = get_macho_binary(file);

	if (bin->error)
		return (nm_process_error(bin));
	unget_macho_binary(bin);
}
