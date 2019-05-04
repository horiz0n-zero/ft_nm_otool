/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_process_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:00:14 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 11:54:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static const char			*g_usage[] =
{
	"usage:\n\n",
	"-p --private-header      Display mach file header(s)\n",
	"-h --headers             Display load commands and section(s)\n",
	"-m --multi               Display more information if possible.\n"
};

void						otool_usage(void)
{
	int						index;

	index = 0;
	while (index < (sizeof(g_usage) / sizeof(g_usage[0])))
	{
		write(STDERR_FILENO, g_usage[index], ft_strlen(g_usage[index]));
		++index;
	}
}
