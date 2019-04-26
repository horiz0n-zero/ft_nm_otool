/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:55:52 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/26 13:43:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static const struct s_nmprint			g_nmprint[] =
{
	{
		nm_pr_symbols_j,
		nm_pr_symbols_j
	},
	{
		nm_pr_symbols_m,
		nm_pr_symbols_m32
	},
	{
		nm_pr_symbols,
		nm_pr_symbols32
	}
};

static struct s_nm						g_nm =
{
	0,
	0,
	g_nmprint + 2,
	sort_symbols_alpha
};

static const struct s_argument			g_arguments[256] =
{
	['j'] = {"just-symbol-name", NM_J, 0, NULL},
	['o'] = {"object", NM_O, 0, NULL},
	['m'] = {"multi", NM_M, 0, NULL},

	['g'] = {"global", NM_G, 0, NULL},
	['u'] = {"undefined", NM_U, 0, NULL},
	['c'] = {"cstrings", NM_C, 0, NULL},

	['a'] = {"all", NM_A, 0, NULL},

	['n'] = {"numeric-sort", NM_N, 0, NULL},
	['p'] = {"preserve-sort", NM_P, 0, NULL},
	['r'] = {"reverse-sort", NM_R, 0, NULL}
};

static inline void						nm_process_flags(void)
{
	if (g_nm.flags & NM_J)
		g_nm.print = g_nmprint;
	else if (g_nm.flags & NM_M)
		g_nm.print = g_nmprint + 1;
	if (g_nm.flags & NM_N)
		g_nm.sortfunc = sort_symbols_numeric;
	else if (g_nm.flags & NM_P)
		g_nm.sortfunc = NULL;
}

int										main(int argc, char **argv)
{
	char						*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_nm.flags, &error)))
	{
		ft_fprintf(STDERR_FILENO, "ft_nm: %s\n", error);
		nm_usage();
		return (EXIT_FAILURE);
	}
	nm_process_flags();
	if (g_nm.flags & NM_C)
		nm_process_cstrings(&g_nm, argv);
	else
	{
		if (g_nm.flags & NM_O && !(g_nm.flags & NM_J))
			nm_print_o(&g_nm, argv);
		else
			nm_process_files(&g_nm, argv);
	}
	return (EXIT_SUCCESS);
}
