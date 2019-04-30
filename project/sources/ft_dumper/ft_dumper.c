/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:04:06 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/30 16:52:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

static struct s_dumper			g_dumper =
{
	0,
	0,
	NULL
};

static const struct s_argument	g_arguments[256] =
{
	['o'] = {"output", DUMPER_O, 1, &g_dumper.output},
	['s'] = {"show-crypt", DUMPER_S, 0, NULL},
	['u'] = {"uuid", DUMPER_U, 0, NULL}
};

static const char				*g_usages[] =
{
	"usage:\n\n",
	"-o --output file          generate header into file.\n",
	"-s --show-crypt           Show information about LC_ENCRYPTION_INFO(_64).\n"
	"-u --uuid                 Show Universally Unique IDentifier (UUID)\n",
	"                          a 128-bit value guaranteed to be unique over both space and time.\n"
};

static void						dumper_usage(void)
{
	int							index;

	index = 0;
	while (index < (sizeof(g_usages) / sizeof(g_usages[0])))
	{
		write(STDERR_FILENO, g_usages[index], ft_strlen(g_usages[index]));
		++index;
	}
}

int								main(int argc, char **argv)
{
	char						*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_dumper.flags, &error)))
	{
		ft_fprintf(STDERR_FILENO, "ft_dumper: %s\n", error);
		dumper_usage();
		return (EXIT_FAILURE);
	}
	if (g_dumper.flags & DUMPER_S)
		dumper_show_lc_encryption(argv);
	if (g_dumper.flags & DUMPER_U)
		dumper_show_uuid(argv);
	if (!(g_dumper.flags & (DUMPER_S | DUMPER_U)))
	{
		
	}
	return (EXIT_SUCCESS);
}
