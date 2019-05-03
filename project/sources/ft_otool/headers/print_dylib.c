/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dylib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:43:39 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 16:24:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void								print_dyld_info(
		struct s_loadcommand *const lc)
{
	struct dyld_info_command *const	d = lc->content;

	ft_printf("%22s %u\n", "rebase_off", d->rebase_off);
	ft_printf("%22s %u\n", "rebase_size", d->rebase_size);
	ft_printf("%22s %u\n", "bind_off", d->bind_off);
	ft_printf("%22s %u\n", "bind_size", d->bind_size);
	ft_printf("%22s %u\n", "weak_bind_off", d->weak_bind_off);
	ft_printf("%22s %u\n", "weak_bind_size", d->weak_bind_size);
	ft_printf("%22s %u\n", "lazy_bind_off", d->lazy_bind_off);
	ft_printf("%22s %u\n", "lazy_bind_size", d->lazy_bind_size);
	ft_printf("%22s %u\n", "export_off", d->export_off);
	ft_printf("%22s %u\n", "export_size", d->export_size);
}

void								print_dylib(
		struct s_loadcommand *const lc)
{
	struct dylib_command			*const d = lc->content;

	ft_printf("%22s %s\n", "name", ((char*)lc->content) + d->dylib.name.offset);
	ft_printf("%22s %s", "timestamp", get_timestamp(d->dylib.timestamp));
	ft_printf("%22s %u.%u.%u\n", "current_version",
			d->dylib.current_version >> 16,
			(d->dylib.current_version >> 8) & 0xff,
			d->dylib.current_version & 0xff);
	ft_printf("%22s %u.%u.%u\n", "compatibility_version",
			d->dylib.compatibility_version >> 16,
			(d->dylib.compatibility_version >> 8) & 0xff,
			d->dylib.compatibility_version & 0xff);
}
