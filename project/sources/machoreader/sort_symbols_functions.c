/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 13:55:16 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/21 16:09:50 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

int							sort_symbols_alpha(
		struct s_symbol *const a,
		struct s_symbol *const b)
{
	register const char		*sa;
	register const char		*sb;

	sa = a->name;
	sb = b->name;
	while (*sa && *sb && *sa == *sb)
	{
		++sa;
		++sb;
	}
	return ((int)*sa - *sb);
}
