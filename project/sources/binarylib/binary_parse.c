/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:21:10 by afeuerst          #+#    #+#             */
/*   Updated: 2019/03/21 14:03:05 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binarylib.h"

struct s_binary_file			*binary_parse_file(const char *const path, char **const error)
{
	struct stat					chat;
	const int					fd = open(path, O_RDONLY);
	struct s_binary_file		*file;

	if (fd <= STDERR_FILENO)
		return (NULL);
	if (fstat(fd, &chat) < 0)
		return (NULL);
	file = malloc(sizeof(struct s_binary_file));

	close(fd);
	*error = NULL;
	return (file);
}

void							binary_destroy_file(struct s_binary_file *const file)
{
	free(file);
}
