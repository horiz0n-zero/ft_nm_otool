/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:51:59 by afeuerst          #+#    #+#             */
/*   Updated: 2019/05/03 10:56:56 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "machoreader_shared.h"
#include <time.h>

char				*get_timestamp(const uint32_t timestamp)
{
	static char		buffer[32];
	time_t			ltime;
	struct tm		result;

	ltime = time(NULL);
	localtime_r(&ltime, &result);
	asctime_r(&result, buffer);
	return (buffer);
}
