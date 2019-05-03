/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prebound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:39:30 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 11:43:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void										print_prebound(
		struct s_loadcommand *const lc)
{
	struct prebound_dylib_command *const	d = lc->content;

	ft_printf("%22s %s\n", "name", ((char*)lc->content) +
			d->name.offset);
	ft_printf("%22s %u\n", "nmodules", d->nmodules);
	ft_printf("%22s %s\n", "linked_modules", ((char*)lc->content) +
			d->linked_modules.offset);
}
