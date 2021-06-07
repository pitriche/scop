/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:37:03 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/07 15:17:26 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "scop.h"
#include <fcntl.h>		/* open */
#include <unistd.h>		/* read, close, lseek */
#include <stdlib.h>		/* malloc */
#include <sys/time.h>	/* gettimeofday */
#include <stdio.h>		/* printf */

/* returns a real time microsecond timestamp since epoch */
unsigned long	usec_timestamp(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return ((unsigned long)tv.tv_sec * 1000000UL + (unsigned long)tv.tv_usec);
}

/* reads an entire file and returns a malloced string with the content */
const char		*read_file(const char *filename)
{
	char	*content;
	int		fd;
	size_t	file_size;

	fd = open(filename, 'r');
	if (fd < 0)
	{
		printf("Cannot open file [%s]\n", filename);
		exit(0);
	}

	/* get file size */
	file_size = (size_t)lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	content = malloc(file_size + 1);
	read(fd, content, file_size);
	content[file_size] = 0;
	close(fd);
	return (content);
}

/* 0 fill a memory field */
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
