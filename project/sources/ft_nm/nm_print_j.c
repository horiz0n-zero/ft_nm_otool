/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_print_j.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:59:57 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/26 10:40:45 by afeuerst         ###   ########.fr       */
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
		if ((symbol + index)->skip)
			continue ;
		ft_printf("%s\n", (symbol + index)->name);
	}
}
