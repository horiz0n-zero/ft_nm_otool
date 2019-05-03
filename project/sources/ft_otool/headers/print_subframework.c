/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_subframework.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:16:47 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 11:39:25 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void									print_subframework(
		struct s_loadcommand *const lc)
{
	struct sub_framework_command *const	s = lc->content;

	ft_printf("%22s %s\n", "umbrella", ((char*)lc->content) + s->umbrella.offset);
}

void									print_subclient(
		struct s_loadcommand *const lc)
{
	struct sub_client_command *const	s = lc->content;

	ft_printf("%22s %s\n", "client", ((char*)lc->content) +
				s->client.offset);
}

void									print_subumbrella(
		struct s_loadcommand *const lc)
{
	struct sub_umbrella_command *const	s = lc->content;

	ft_printf("%22s %s\n", "sub_umbrella", ((char*)lc->content) + s->sub_umbrella.offset);
}

void									print_sublibrary(
	struct s_loadcommand *const lc)
{
	struct sub_library_command *const	s = lc->content;

	ft_printf("%22s %s\n", "sub_library", ((char*)lc->content) + s->sub_library.offset);
}
