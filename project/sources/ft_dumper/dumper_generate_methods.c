/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_methods.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:20:18 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/06 15:50:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void			dumper_generate_methods(
		struct s_dumper *const dumper,
		struct s_method *methods, int count,
		const int isclass, const char *const prefix)
{
	if (isclass)
	{
		while (count--)
		{
			ft_fprintf(dumper->fdoutput, "%s+(%s) %s;\n", prefix, methods->types, methods->name);
			methods++;
		}
	}
	else
	{
		while (count--)
		{
			ft_fprintf(dumper->fdoutput, "%s-(%s) %s;\n", prefix, methods->types, methods->name);
			methods++;
		}
	}
}











