/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:47:43 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/24 12:59:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void					nm_pr_symbols32(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count)
{
	int					index;
	struct s_symbol		*ptr;

	index = 0;
	while (index < count)
	{
		ptr = symbols + index++;
		if (ptr->skip)
			continue ;
		if (ptr->value)
			ft_printf("%08llx %c %s\n", ptr->value, get_nlist_extchar(ptr), ptr->name);
		else
			ft_printf("         %c %s\n", get_nlist_extchar(ptr), ptr->name);
	}
}

void					nm_pr_symbols(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count)
{
	int					index;
	struct s_symbol		*ptr;

	index = 0;
	while (index < count)
	{
		ptr = symbols + index++;
		if (ptr->skip)
			continue ;
		if (ptr->value)
			ft_printf("%016llx %c %s\n", ptr->value, get_nlist_extchar(ptr), ptr->name);
		else
			ft_printf("                 %c %s\n", get_nlist_extchar(ptr), ptr->name);
	}
}
