/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_class.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:03:32 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/07 10:21:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static inline void	generate_class_header(
		struct s_dumper *const dumper,
		struct s_class *const c)
{
	char *const		super = c->superclass ? c->superclass->name : "NSObject";

	if (c->instances)
	{
		ft_fprintf(dumper->fdoutput, "@interface %s: %s%s {\n", c->name, super,
			c->protocols ? protocols_list(c->protocols, c->protocols_count) : "");
		dumper_generate_instances(dumper, c->instances, c->instances_count, "\t");
		ft_fprintf(dumper->fdoutput, "}\n\n");
	}
	else
	{
		ft_fprintf(dumper->fdoutput, "@interface %s: %s%s\n\n", c->name, super,
			c->protocols ? protocols_list(c->protocols, c->protocols_count) : "");
	}
}

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
		generate_class_header(dumper, c);
		if (c->properties)
			dumper_generate_properties(dumper, c->properties, c->properties_count, "");
		if (c->methods_count)
			dumper_generate_methods(dumper, c->methods, c->methods_count, 0, "");
		if (c->metaclass && c->metaclass->methods_count)
			dumper_generate_methods(dumper, c->metaclass->methods, c->metaclass->methods_count, 1, "");
		ft_fprintf(dumper->fdoutput, "\n@end\n\n");
	}
}
