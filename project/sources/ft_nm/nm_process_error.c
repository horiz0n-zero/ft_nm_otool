/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:12:08 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/21 14:36:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void				nm_process_error(struct s_macho_binary *const bin)
{
	ft_fprintf(STDERR_FILENO, "ft_nm: %s: %s.\n\n", bin->file, bin->error);
	unget_macho_binary(bin);
}
