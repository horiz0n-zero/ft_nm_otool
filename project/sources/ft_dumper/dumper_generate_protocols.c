/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_protocols.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:15:07 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/07 09:45:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

char					*protocols_list(struct s_protocol *protocols, int count)
{
	static char			buffer[2048];
	char				*ptr;
	char				*name;

	ptr = buffer;
	*ptr++ = ' ';
	*ptr++ = '<';
	while (count--)
	{
		name = protocols->name;
		while (*name)
			*ptr++ = *name++;
		protocols++;
		if (count)
		{
			*ptr++ = ',';
			*ptr++ = ' ';
		}
	}
	*ptr++ = '>';
	*ptr = 0;
	return (buffer);
}

void					dumper_generate_protocols(struct s_dumper *const dumper)
{
	int					i;
	struct s_protocol	*p;

	i = 0;
	while (i < dumper->protocols_count)
	{
		p = dumper->protocols + i++;
		ft_fprintf(dumper->fdoutput, "@protocol %s%s\n\n", p->name,
				p->protocols ? protocols_list(p->protocols, p->protocols_count) : "");
		if (p->class_methods_count || p->instance_methods_count)
			ft_fprintf(dumper->fdoutput, "@required\n");
		if (p->class_methods_count)
			dumper_generate_methods(dumper, p->class_methods, p->class_methods_count, 1, "\t");
		if (p->instance_methods_count)
			dumper_generate_methods(dumper, p->instance_methods, p->instance_methods_count, 0, "\t");
		if (p->o_class_methods_count || p->o_instance_methods_count)
			ft_fprintf(dumper->fdoutput, "@optional\n");
		if (p->o_class_methods_count)
			dumper_generate_methods(dumper, p->o_class_methods, p->o_class_methods_count, 1, "\t");
		if (p->o_instance_methods_count)
			dumper_generate_methods(dumper, p->o_instance_methods, p->o_instance_methods_count, 0, "\t");
		ft_fprintf(dumper->fdoutput, "@end\n\n");
	}
}


















