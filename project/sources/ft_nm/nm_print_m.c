/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_print_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 09:31:25 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/23 12:53:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void				nm_pr_symbols_m32(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count)
{
	int				index;
	struct s_symbol	*ptr;

	index = 0;
	while (index < count)
	{
		ptr = symbols + index++;
		if (ptr->skip)
			continue ;
		if (ptr->value)
			ft_printf("%08llx %s%s\n", ptr->value, get_nlist_ext(ptr), ptr->name);
		else
			ft_printf("         %s%s%s\n", get_nlist_ext(ptr),  ptr->name, get_nlist_library(macho, ptr));
	}
}

void				nm_pr_symbols_m(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count)
{
	int				index;
	struct s_symbol	*ptr;

	index = 0;
	while (index < count)
	{
		ptr = symbols + index++;
		if (ptr->skip)
			continue ;
		if (ptr->value)
			ft_printf("%016llx %s%s\n", ptr->value, get_nlist_ext(ptr), ptr->name);
		else
			ft_printf("                 %s%s%s\n", get_nlist_ext(ptr),  ptr->name, get_nlist_library(macho, ptr));
	}
}
