/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre42 <pierre42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:37:03 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/09 16:33:42 by pierre42         ###   ########.fr       */
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
char			*read_file(const char *filename)
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

#define IMAGE_RESOLUTION	(1200 * 675)

float			*load_bmp(const char *filename)
{
	unsigned char	buffer[1000];
	float			*pixels;
	int				fd;
	unsigned		offset;

	fd = open(filename, 'r');
	if (fd < 0)
	{
		printf("Cannot open file [%s]\n", filename);
		exit(0);
	}

	/* go to byte array */
	read(fd, buffer, 14);
	offset = *(unsigned *)(buffer + 10);
	lseek(fd, offset, SEEK_SET);

	pixels = malloc(IMAGE_RESOLUTION * 3 * sizeof(float));
	for (unsigned i = 0; i < IMAGE_RESOLUTION; ++i)
	{
		if (read(fd, buffer, 4) != 4)
		{
			printf("Corrupted texture %d\n", i);
			exit(0);
		}
		pixels[i * 3 + 0] = buffer[2] / 255.0f;
		pixels[i * 3 + 1] = buffer[1] / 255.0f;
		pixels[i * 3 + 2] = buffer[0] / 255.0f;
	}
	close(fd);
	return (pixels);
}
