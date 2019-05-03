/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fvmlib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:37:15 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 11:06:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void						print_fvmlib(struct s_loadcommand *const lc)
{
	struct fvmlib_command	*const f = lc->content;

	ft_printf("%22s %u\n", "minor_version", f->fvmlib.minor_version);
	ft_printf("%22s %u\n", "header_addr", f->fvmlib.header_addr);
}
