/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader_shared.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:56:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 14:37:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHOREADER_SHARED_H
# define MACHOREADER_SHARED_H

# include <unistd.h> // close - write
# include <stdlib.h> // malloc - free
# include <fcntl.h> // open
# include <sys/stat.h> // fstat
# include <sys/mman.h> // mmap - munmap

size_t								ft_strlen(const char *const src);
int									ft_strcmp(const char *s1, const char *s2);
void								mem_swap32(void *const content, size_t size);
void								mem_swap64(void *const content, size_t size);

void								fatalerror(const char *const error);

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

# define W(str) write(STDOUT_FILENO, str, sizeof(str))

#endif
