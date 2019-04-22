/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_macho_binary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:54:05 by afeuerst          #+#    #+#             */
/*   Updated: 2019/04/21 13:25:29 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader.h"

inline void						*getset_object(struct s_macho_binary *const binary, void **const seek, const size_t size)
{
	register char *const		end_str = ((char*)binary->content) + binary->content_size;
	register void *const		current_seek = *seek;
	register char *const		offset_str = ((char*)current_seek) + size;

	if (offset_str <= end_str)
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
	register char *const		offset_str = ((char*)current_seek) + size;

	if (offset_str <= end_str)
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
		return (set_error(binary, MRERR_DENIED));
	binary->position = binary->content;
	if (!(fat = GETO(binary, binary->position, struct fat_header)))
		return (set_error(binary, MRERR_MACHO));
	if (read_fat_header(binary, fat))
		return ;
	binary->macho = ft_memalloc(sizeof(struct s_macho));
	binary->count = 1;
	read_macho_header(binary, binary->macho);
}

struct s_macho_binary			*get_macho_binary(const char *file)
{
	struct s_macho_binary		*binary;
	const int					fd = open(file, O_RDONLY);
	struct stat					buf;
	struct stat					lbuf;

	binary = ft_memalloc(sizeof(struct s_macho_binary));
	binary->file = file;
	if (fd < 0)
		binary->error = MRERR_NOTFOUND;
	else
	{
		if (fstat(fd, &buf))
			binary->error = MRERR_DENIED;
		else
		{
			if (buf.st_mode & S_IFLNK && lstat(file, &lbuf))
				binary->error = MRERR_NOTFOUND;
			else if (buf.st_mode & S_IFDIR)
				binary->error = MRERR_ISDIR;
			else if (!(buf.st_mode & S_IFREG))
				binary->error = MRERR_NOTREF;
			else
				read_macho_binary_file(binary, &buf, fd);
		}
		close(fd);
	}
	return (binary);
}
