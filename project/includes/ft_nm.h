/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:43:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/20 17:22:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "machoreader.h"

typedef struct s_nmprint	t_nmprint;

struct						s_nm
{
	int						flags;
# define NM_J 1 << 0
# define NM_O 1 << 1
# define NM_M 1 << 2

# define NM_G 1 << 3
# define NM_U 1 << 4
# define NM_C 1 << 5

# define NM_N 1 << 6
# define NM_P 1 << 7
# define NM_R 1 << 8
	int						pad;
	const struct s_nmprint	*print;
};

struct						s_nmprint
{
	void					(*pr_symbols)(struct s_symbol *symbols, int count);
	void					(*pr_symbols_32)(struct s_symbol *symbols, int count);
};

# define DEFAULT_BIN "a.out"

void						nm_process_file(
		struct s_nm *const nm,
		const char *const file);

void						nm_process_cstrings(
		struct s_nm *const nm,
		char **argv);

void						nm_process_error(
		struct s_macho_binary *const bin);

#endif
