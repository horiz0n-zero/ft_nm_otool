/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader_shared.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:56:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/04 10:36:06 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHOREADER_SHARED_H
# define MACHOREADER_SHARED_H

# include "libprintf.h"

# include <unistd.h> // close - write
# include <stdlib.h> // malloc - free
# include <fcntl.h> // open
# include <sys/stat.h> // fstat
# include <sys/mman.h> // mmap - munmap
# include <mach/vm_prot.h> // vm

size_t								ft_strlen(const char *const src);
int									ft_strcmp(const char *s1, const char *s2);
int									ft_strncmp(const void *const p1, const void *const p2, int length);
void								*ft_memalloc(size_t size);
int									ft_atoi(const char *src);
char								*str_push(const char *src, char *ptr);
char								*number_push(int number, char *ptr);
void								ft_memmove(
		const void *src,
		void *dst,
		size_t size);

struct								s_argument
{
	const char						*name;
	const int						flags;
	const int						require;
	char **const					required;
};

char								**arguments_get(char **argv,
		const struct s_argument *const arguments,
		int *const flags,
		char **const error);

typedef struct s_macho_binary		t_macho_binary;

int									select_arch(
		struct s_macho_binary *const binary,
		int *const select);

char								*get_timestamp(const uint32_t timestamp);
const char							*get_vm_prot(const vm_prot_t prot);

#endif
