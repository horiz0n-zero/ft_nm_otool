/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_twolevel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:18:49 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 13:26:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			print_two_level(
		struct s_loadcommand *const lc)
{
	struct twolevel_hints_command *const	t = lc->content;

	ft_printf("%22s %u\n", "offset", t->offset);
	ft_printf("%22s %u\n", "nhints", t->nhints);
}
