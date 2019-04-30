/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_process_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:00:14 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/30 11:56:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static const char			*g_usage[] =
{
	"usage:\n\n",
	"-p --private-header      Display only the first format specific file header\n",
	"-s --syntax syntax       ASM syntax to use.\n"
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
