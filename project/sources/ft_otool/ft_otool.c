/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:57:45 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/09 14:27:50 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

#include <stdio.h>
int								main(int argc, char **argv)
{
	struct s_macho_binary		*macho;

	macho = get_macho_binary(*argv);
	if (macho->error)
		write(STDOUT_FILENO, macho->error, ft_strlen(macho->error));
	else
	{
		printf("%zd %p\n", macho->content_size, macho->content);
	}
	unget_macho_binary(macho);
	return (0);
}
