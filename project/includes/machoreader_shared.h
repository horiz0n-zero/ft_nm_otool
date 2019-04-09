/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machoreader_shared.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:56:48 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/09 13:28:42 by afeuerst         ###   ########.fr       */
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

#endif
