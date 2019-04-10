/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 10:38:23 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 11:10:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"

void			fatalerror(const char *const error)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	exit(EXIT_FAILURE);
}
