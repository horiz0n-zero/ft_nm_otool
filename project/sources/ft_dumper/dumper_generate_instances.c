/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_instances.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:45:17 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/07 10:21:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void			dumper_generate_instances(
		struct s_dumper *const dumper,
		struct s_instance_var *ivars, int count,
		const char *const prefix)
{
	while (count--)
	{// padding aligned to protocol ???
		ft_fprintf(dumper->fdoutput, "%s%s\t%s;\n", prefix,
				ivars->type, ivars->name);
		ivars++;
	}
}
