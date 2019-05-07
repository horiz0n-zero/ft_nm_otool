/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_properties.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:10:04 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/07 15:00:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void		dumper_generate_properties(struct s_dumper *const dumper,
		struct s_property *properties, int count,
		const char *const prefix)
{
	while (count--)
	{// padding
		ft_fprintf(dumper->fdoutput, "%s@property (%s) %s\t%s;\n", prefix,
				properties->attributes, "name", properties->name);
		properties++;
	}
	write(dumper->fdoutput, "\n", 1);
}
