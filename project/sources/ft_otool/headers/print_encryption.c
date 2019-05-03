/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_encryption.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:41:00 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 14:18:05 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void											print_encry(
		struct s_loadcommand *const lc)
{
	struct encryption_info_command *const		e = lc->content;

	ft_printf("%22s %u\n", "cryptoff", e->cryptoff);
	ft_printf("%22s %u\n", "cryptsize", e->cryptsize);
	ft_printf("%22s %u\n", "cryptid", e->cryptid);
}
