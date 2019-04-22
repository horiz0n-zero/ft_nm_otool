/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_print_j.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:59:57 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/22 13:56:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

void				nm_pr_symbols_j(
		struct s_macho *const macho,
		struct s_symbol *const symbol,
		int count)
{
	int				index;

	index = -1;
	while (++index < count)
	{
		if (!(symbol + index)->section ||
			(symbol + index)->type & N_STAB ||
			!*(symbol + index)->name)
			continue ;
		ft_printf("%s\n", (symbol + index)->name);
	}
}
