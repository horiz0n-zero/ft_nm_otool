/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uuid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:28:04 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 13:34:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void							print_uuid(
		struct s_loadcommand *const lc)
{
	struct uuid_command *const	u = lc->content;

	ft_printf("%22s %08X-%04hX-%04hX-%04hX-%08X%04hX\n",
			"uuid",
			__builtin_bswap32(*(uint32_t*)u->uuid),
			__builtin_bswap16(*(uint16_t*)(u->uuid + 4)),
			__builtin_bswap16(*(uint16_t*)(u->uuid + 6)),
			__builtin_bswap16(*(uint16_t*)(u->uuid + 8)),
			__builtin_bswap32(*(uint32_t*)(u->uuid + 10)),
			__builtin_bswap16(*(uint16_t*)(u->uuid + 14)));
}
