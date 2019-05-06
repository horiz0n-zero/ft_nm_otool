/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_class.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:03:32 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/06 16:14:29 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void				dumper_generate_class(struct s_dumper *const dumper)
{
	int				i;
	struct s_class	*c;

	i = 0;
	while (i < dumper->class_count)
	{
		c = dumper->class + i++;
		if (c->isswift)
			continue ;
		ft_fprintf(dumper->fdoutput, "@interface %s: %s\n\n", c->name,
				c->superclass ? c->superclass->name : "NSObject");
		if (c->methods_count)
			dumper_generate_methods(dumper, c->methods, c->methods_count, 0, "");
		if (c->metaclass && c->metaclass->methods_count)
			dumper_generate_methods(dumper, c->metaclass->methods, c->metaclass->methods_count, 1, "");
		ft_fprintf(dumper->fdoutput, "\n@end\n\n");
	}
}
