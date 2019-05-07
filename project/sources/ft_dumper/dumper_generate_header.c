/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_generate_header.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:09:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/06 16:17:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"
#include <time.h>

static void				*dumper_generate_header_date(void)
{
	time_t				now;
	struct tm			*local;
	static char			buffer[42];

	time(&now);
	local = localtime(&now);
	ft_bprintf(buffer, "%0.2d/%0.2d/%0.4d %0.2d:%0.2d:%0.2d",
			local->tm_mday,
			local->tm_mon + 1,
			local->tm_year + 1900,
			local->tm_hour,
			local->tm_min,
			local->tm_sec);
	return (buffer);
}

static int				header_args_max_size(int count, ...)
{
	va_list				args;
	int					len;
	int					tmp;

	len = 0;
	va_start(args, count);
	while (count--)
	{
		tmp = (int)ft_strlen(va_arg(args, char*));
		if (tmp > len)
			len = tmp;
	}
	va_end(args);
	return (len + 2);
}

void					dumper_generate_header(
		struct s_dumper *const dumper,
		struct s_macho_binary *const bin)
{
	const int			o = dumper->fdoutput;
	static const char	author[] = "ft_dumper by Antoine feuerstein";
	int					max;
	char				*buffer;

	max = header_args_max_size(2, author, bin->file);
	buffer = ft_static_itoa(max);
	ft_fprintf(o, static_strjoins(3, "/* %", buffer, "s  *\n"), " ");
	ft_fprintf(o, static_strjoins(3, "** %-", buffer, "s **\n"), author);
	ft_fprintf(o, static_strjoins(3, "** %", buffer, "s **\n"), " ");
	ft_fprintf(o, static_strjoins(3, "** %-", buffer, "s **\n"), bin->file);
	ft_fprintf(o, static_strjoins(3, "** %", buffer, "s **\n"), " ");
	ft_fprintf(o, static_strjoins(3, "** %", buffer, "s **\n"), dumper_generate_header_date());
	ft_fprintf(o, static_strjoins(3, "*/ %", buffer, "s *\n\n"), " ");
	if (dumper->protocols_count)
		dumper_generate_protocols(dumper);
	dumper_generate_class(dumper);
}
