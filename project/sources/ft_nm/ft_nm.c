/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:55:52 by afeuerst          #+#    #+#             */
/*   Updated: 2019/03/21 14:03:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int						main(int argc, char **argv)
{
	char				*error;
	void				*value;

	value = binary_parse_file(*argv, &error);
	return (0);
}
