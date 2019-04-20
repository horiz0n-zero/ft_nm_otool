/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_process_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 16:12:08 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 17:23:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// set exit_failure at last value ?

void				nm_process_error(struct s_macho_binary *const bin)
{
	ft_fprintf(STDERR_FILENO, "ft_nm:%s\n", bin->error);
	unget_macho_binary(bin);
}
