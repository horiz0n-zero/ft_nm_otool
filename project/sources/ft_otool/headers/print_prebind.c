/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prebind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:26:28 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 13:27:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void									print_prebind(
		struct s_loadcommand *const lc)
{
	struct prebind_cksum_command *const	p = lc->content;

	ft_printf("%22s %u\n", "cksum", p->cksum);
}
