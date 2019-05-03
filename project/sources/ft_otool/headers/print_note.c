/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_note.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:43:58 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 17:03:39 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void							print_note(
		struct s_loadcommand *const lc)
{
	struct note_command *const	n = lc->content;
	int					index;

	index = 0;
	ft_printf("%22s ", "data_owner");
	while (index < 16 && n->data_owner[index])
		write(STDOUT_FILENO, n->data_owner + index++, 1);
	ft_printf("\n%22s %llu\n", "offset", n->offset);
	ft_printf("%22s %llu\n", "size", n->size);
}
