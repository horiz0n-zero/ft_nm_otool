/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:55:52 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 17:54:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static struct s_nm						g_nm =
{
	0,
	0,
	NULL
};

static const struct s_argument			g_arguments[256] =
{
	['j'] = {"just-name", NM_J, 0, NULL},
	['o'] = {"object", NM_O, 0, NULL},
	['m'] = {"multiple", NM_M, 0, NULL},

	['g'] = {"global", NM_G, 0, NULL},
	['u'] = {"undefined", NM_U, 0, NULL},
	['c'] = {"cstrings", NM_C, 0, NULL},

	['n'] = {"numeric-sort", NM_N, 0, NULL},
	['p'] = {"preserve-sort", NM_P, 0, NULL},
	['r'] = {"reverse-sort", NM_R, 0, NULL}
};

int										main(int argc, char **argv)
{
	char						*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_nm.flags, &error)))
	{
		ft_fprintf(STDERR_FILENO, "ft_nm: %s\n", error);
		return (EXIT_FAILURE);
	}
	if (g_nm.flags & NM_C)
		nm_process_cstrings(&g_nm, argv);
	else
	{
		;
	}
	return (EXIT_SUCCESS);
}






