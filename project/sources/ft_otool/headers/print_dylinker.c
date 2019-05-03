/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dylinker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:43:34 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 11:50:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void								print_dylinker(
		struct s_loadcommand *const lc)
{
	struct dylinker_command *const	d = lc->content;

	ft_printf("%22s %s\n", "name", ((char*)lc->content) +
				d->name.offset);
}
