/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:29:51 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 08:52:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void							print_rpath(
		struct s_loadcommand *const lc)
{
	struct rpath_command *const	r = lc->content;

	ft_printf("%22s %s\n", "path", ((char*)lc->content) + r->path.offset);
}
