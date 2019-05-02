/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_header.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:09:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/02 10:45:02 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"
#include <time.h>

static inline void		dumper_generate_header_print_date(const int fd)
{
	time_t				now;
	struct tm			*local;

	time(&now);
	local = localtime(&now);
	ft_fprintf(fd, "%0.2d/%0.2d/%0.2d %0.2d:%0.2d:%0.2d\n",
			local->tm_mday,
			local->tm_mon + 1,
			local->tm_year + 1900,
			local->tm_hour,
			local->tm_min,
			local->tm_sec);
}

void					dumper_generate_header(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin)
{
	ft_fprintf(dumper->fdoutput, "/*\n");
	ft_fprintf(dumper->fdoutput, " *\n");
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " * * ft_dumper Copyright (C) Antoine Feuerstein\n");
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " * * image source: %s\n", bin->file);
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " * * header generated at ");
	dumper_generate_header_print_date(dumper->fdoutput);
	ft_fprintf(dumper->fdoutput, "* *\n");
	ft_fprintf(dumper->fdoutput, " *\n");
	ft_fprintf(dumper->fdoutput, "*/\n\n");
}
