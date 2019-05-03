/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_linkedit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:35:21 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 13:40:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void									print_linkedit(
		struct s_loadcommand *const lc)
{
	struct linkedit_data_command *const	l = lc->content;

	ft_printf("%22s %u\n", "dataoff", l->dataoff);
	ft_printf("%22s %u\n", "datasize", l->datasize);
}
