/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:37:03 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/04 10:23:02 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>		/* open */
#include <unistd.h>		/* read, close, lseek */
#include <stdlib.h>		/* malloc */
#include <sys/time.h>	/* gettimeofday */

unsigned long	usec_timestamp(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return ((unsigned long)tv.tv_sec * 1000000UL + (unsigned long)tv.tv_usec);
}

const char		*read_file(const char *filename)
{
	char	*content;
	int		fd;
	size_t	file_size;

	fd = open(filename, 'r');

	/* get file size */
	file_size = (size_t)lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	content = malloc(file_size + 1);
	read(fd, content, file_size);
	content[file_size] = 0;
	close(fd);
	return (content);
}

void			ft_bzero(void *ptr, size_t size)
{
	while (size & 0b111)
	{
		--size;
		*((char *)ptr + size) = 0;
	}
	while (size >= 8)
	{
		size -= 8;
		*((long *)ptr + (size >> 3)) = 0;
	}
}
