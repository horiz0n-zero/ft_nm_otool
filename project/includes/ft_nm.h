/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:43:50 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/01 15:38:29 by afeuerst         ###   ########.fr       */
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
# define NM_A 1 << 9
# define NM_S 1 << 10
# define NM_D 1 << 11

	int						pad;
	const struct s_nmprint	*print;
	int						(*sortfunc)(
			struct s_symbol *const a,
			struct s_symbol *const b);
};

struct						s_nmprint
{
	void					(*pr_symbols)(
			struct s_macho *const macho,
			struct s_symbol *const symbols,
			int count);
	void					(*pr_symbols_32)(
			struct s_macho *const macho,
			struct s_symbol *const symbols,
			int count);
};
void						nm_pr_symbols_j(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count);
void						nm_pr_symbols_m(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count);
void						nm_pr_symbols_m32(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count);
void						nm_pr_symbols(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count);
void						nm_pr_symbols32(
		struct s_macho *const macho,
		struct s_symbol *const symbols,
		int count);

void						nm_print_o(
		struct s_nm *const nm,
		char **argv);

# define DEFAULT_BIN "a.out"

void						nm_process_skipable(
		struct s_nm *const nm,
		struct s_macho *const macho);

void						nm_process_files(
		struct s_nm *const nm,
		char **argv);
void						nm_process_file(
		struct s_nm *const nm,
		struct s_macho_binary *const bin);

void						nm_process_strings(
		struct s_nm *const nm,
		char **argv);

void						nm_process_error(
		struct s_macho_binary *const bin);
void						nm_usage(void);

#endif
