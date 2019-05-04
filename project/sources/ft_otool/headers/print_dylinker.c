/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dylinker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:43:34 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 10:42:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void								print_dylinker(
		struct s_loadcommand *const lc)
{
	struct dylinker_command *const	d = lc->content;

	if (lc->pad)
		d->name.offset = __builtin_bswap32(d->name.offset);
	ft_printf("%22s %s\n", "name", ((char*)lc->content) +
				d->name.offset);
}
