/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:55:52 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/09 14:22:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static struct s_nm				g_nm =
{
	0,
	NULL,
	NULL
};

static const struct s_argument	g_arguments[256] =
{
	['i'] = {"input", 1, 1, &g_nm.in},
	['s'] = {"server", 2, 0, NULL},
	['o'] = {"output", 4, 1, &g_nm.out}
};

#include <stdio.h>
int						main(int argc, char **argv)
{
	char				*error;

	if (!(argv = arguments_get(++argv, g_arguments, &g_nm.flags, &error)))
		write(STDERR_FILENO, error, ft_strlen(error));
	else
		printf("%d %s\n%s\n", g_nm.flags, *argv, g_nm.in);
	return (0);
}






