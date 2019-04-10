/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:54:05 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/10 14:31:54 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

inline void						*getset_object(struct s_macho_binary *const binary, void **const seek, const size_t size)
{
	register char *const		end_str = ((char*)binary->content) + binary->content_size;
	register void *const		current_seek = *seek;
	register char *const		offset_str = ((char*)(current_seek)) + size;

	if (offset_str < end_str)
	{
		*seek = offset_str;
		return (current_seek);
	}
	else
		return (NULL);
}

inline void						*get_object(struct s_macho_binary *const binary, void *const seek, const size_t size)
{
	register char *const		end_str = ((char*)binary->content) + binary->content_size;
	register void *const		current_seek = seek;
	register char *const		offset_str = ((char*)(current_seek)) + size;

	if (offset_str < end_str)
		return (current_seek);
	else
		return (NULL);
}

inline void						set_object(struct s_macho_binary *const binary, const size_t size)
{
	register char *const		offset = ((char*)binary->position) + size;

	binary->position = offset;
}

static inline void				read_macho_binary_file(struct s_macho_binary *const binary,
		struct stat *buf, const int fd)
{
	struct fat_header			*fat;

	binary->content_size = (size_t)buf->st_size;
	if ((binary->content = mmap(NULL, binary->content_size,
					PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (set_error(binary, "cannot read"));
	binary->position = binary->content;
	if (!(fat = GETO(binary, binary->position, struct fat_header)))
		return (set_error(binary, "size < fat header"));
	if (read_fat_header(binary, fat))
		return ;
	binary->macho = malloc(sizeof(struct s_macho));
	binary->count = 1;
	read_macho_header(binary, binary->macho);
}

struct s_macho_binary			*get_macho_binary(const char *file)
{
	struct s_macho_binary		*binary;
	const int					fd = open(file, O_RDONLY);
	struct stat					buf;

	binary = malloc(sizeof(struct s_macho_binary));
	binary->file = file;
	binary->error = NULL;
	binary->macho = NULL;
	if (fd < 0)
		binary->error = "file not found";
	else
	{
		if (fstat(fd, &buf))
			binary->error = "fstat failure";
		else
			read_macho_binary_file(binary, &buf, fd);
		close(fd);
	}
	return (binary);
}
