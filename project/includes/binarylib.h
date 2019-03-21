/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarylib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:41:57 by afeuerst          #+#    #+#             */
/*   Updated: 2019/03/21 14:02:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYLIB_H
# define BINARYLIB_H

# include <unistd.h> // close - write
# include <stdlib.h> // malloc - free
# include <fcntl.h> // open
# include <sys/stat.h> // fstat
# include <sys/mman.h> // mmap - munmap

# include <mach-o/arch.h>
# include <mach-o/compact_unwind_encoding.h>
# include <mach-o/dyld.h>
# include <mach-o/dyld_images.h>
# include <mach-o/fat.h>
# include <mach-o/getsect.h>
# include <mach-o/ldsyms.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <mach-o/reloc.h>
# include <mach-o/stab.h>
# include <mach-o/swap.h>

typedef struct s_binary_file		t_binary_file;

struct								s_binary_file
{
	void							*content;
	size_t							size;
};

struct s_binary_file				*binary_parse_file(const char *const path, char **const error);
void								binary_destroy_file(struct s_binary_file *const file);


void								*binary_error(const int id, char **const error, int64_t arg1, int64_t arg2);
# define OPEN_FAILED 0

#endif
