/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dumper.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:03:19 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/30 13:07:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DUMPER_H
# define FT_DUMPER_H

# include "machoreader.h"

struct								s_dumper
{
	int								flags;
# define DUMPER_O 1 << 0
# define DUMPER_S 1 << 1
	int								pad;

	char							*output;
};

void								dumper_show_lc_encryption(char **argv);

#endif
