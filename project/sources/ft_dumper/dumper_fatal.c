/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_fatal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 11:55:10 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 14:16:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dumper.h"

void			dumper_fatal(const char *const error)
{
	ft_printf(error);
	exit(1);
}