/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:57:45 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 09:59:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static struct s_otool				g_otool =
{
	0,
	0,
	NULL,
	otool_content_default_32,
	otool_content_default_64
};

static const struct s_argument		g_arguments[256] =
{
	['p'] = {"private-header", OTOOL_P, 0, NULL},
	['h'] = {"headers", OTOOL_H, 0, NULL},
	['m'] = {"multi", OTOOL_M, 0, NULL}
};

int								main(int argc, char **argv)
{
	char						*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_otool.flags, &error)) ||
		(!*argv && (error = "at least one file must be specified")))
	{
		ft_fprintf(STDERR_FILENO, "ft_otool: %s\n", error);
		otool_usage();
		return (EXIT_FAILURE);
	}
	otool_process_files(&g_otool, argv);
	return (0);
}
