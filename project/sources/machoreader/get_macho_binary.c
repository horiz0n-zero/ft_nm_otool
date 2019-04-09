/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:54:05 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/09 14:49:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

inline const void				*get_object(struct s_macho_binary *const binary, const void *const seek, const size_t size)
{
	register const char *const	end_str = ((const char*)binary->content) + binary->content_size;
	register const char *const	offset_str = ((const char*)(seek)) + size;

	if (offset_str < end_str)
		return (seek);
	else
		return (NULL);
}

static inline void				get_macho_binary_file(struct s_macho_binary *const binary,
		struct stat *buf, const int fd)
{
	struct fat_header			*fat;

	binary->content_size = (size_t)buf->st_size;
	binary->content = malloc(binary->content_size);
	if ((binary->content = mmap(NULL, binary->content_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		binary->error = "cannot read";
		return ;
	}
	fat = OBJECT(struct fat_header, binary, binary->content);
	if (fat == NULL)
		write(STDOUT_FILENO, "bad header", 10);
	else
		write(STDOUT_FILENO, &fat, 4);
}

struct s_macho_binary			*get_macho_binary(const char *file)
{
	struct s_macho_binary		*binary;
	const int					fd = open(file, O_RDONLY);
	struct stat					buf;

	binary = malloc(sizeof(binary));
	binary->file = file;
	binary->content = NULL;
	binary->content_size = 0;
	binary->macho = NULL;
	binary->error = NULL;
	binary->count = 0;
	if (fd < 0)
		binary->error = "file not found";
	else
	{
		if (fstat(fd, &buf))
			binary->error = "fstat failure";
		else
			get_macho_binary_file(binary, &buf, fd);
		close(fd);
	}
	return (binary);
}
