/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_instances.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:45:17 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/09 10:16:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void			dumper_generate_instances(
		struct s_dumper *const dumper,
		struct s_instance_var *ivars, int count,
		const char *const prefix)
{
	int			array;
	const char	*type;

	array = 0;
	while (count--)
	{
		type = get_primitive_instance_type(dumper, ivars->type, &array);
		if (array)
		{
			ft_fprintf(dumper->fdoutput, "%s%s %s[%d];\n", prefix, type,
					ivars->name, array);
			array = 0;
		}
		else
			ft_fprintf(dumper->fdoutput, "%s%s\t%s;\n", prefix, type, ivars->name);
		ivars++;
	}
}
