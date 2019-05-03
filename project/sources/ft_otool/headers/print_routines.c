/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:51:02 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 12:40:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void									print_routines(
		struct s_loadcommand *const lc)
{
	struct routines_command *const		d = lc->content;

	ft_printf("%22s %u\n", "init_address", d->init_address);
	ft_printf("%22s %u\n", "init_module", d->init_module);
	ft_printf("%22s %u\n", "reserved1", d->reserved1);
	ft_printf("%22s %u\n", "reserved2", d->reserved2);
	ft_printf("%22s %u\n", "reserved3", d->reserved3);
	ft_printf("%22s %u\n", "reserved4", d->reserved4);
	ft_printf("%22s %u\n", "reserved5", d->reserved5);
	ft_printf("%22s %u\n", "reserved6", d->reserved6);
}

void									print_routines64(
		struct s_loadcommand *const lc)
{
	struct routines_command_64 *const	d = lc->content;

	ft_printf("%22s %llu\n", "init_address", d->init_address);
	ft_printf("%22s %llu\n", "init_module", d->init_module);
	ft_printf("%22s %llu\n", "reserved1", d->reserved1);
	ft_printf("%22s %llu\n", "reserved2", d->reserved2);
	ft_printf("%22s %llu\n", "reserved3", d->reserved3);
	ft_printf("%22s %llu\n", "reserved4", d->reserved4);
	ft_printf("%22s %llu\n", "reserved5", d->reserved5);
	ft_printf("%22s %llu\n", "reserved6", d->reserved6);
}
