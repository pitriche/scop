/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre42 <pierre42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 09:46:37 by brunomartin       #+#    #+#             */
/*   Updated: 2021/06/09 17:59:35 by pierre42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "utils.h"	/* read_file */
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* atoi, rand */
#include <limits.h>	/* MAX_INT */

static size_t	next_line(const char *str, size_t current)
{
	size_t	next;

	next = 0;
	while (str[current + next] != 0 && str[current + next] != '\n')
		++next;
	if (str[current + next] != 0)
		++next;
	return (next);
}

static size_t	next_char(const char *str, size_t current)
{
	size_t	next;

	next = 0;
	while (str[current + next] != 0 && str[current + next] == ' ')
		++next;
	return (next);
}

/* ########################################################################## */

static void		parse_vertex(t_all *al, const char *str, size_t current)
{
	static const float	color_palette[6] = {0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f};
	static int			current_color = 0;

	static unsigned	current_vertex = 0;
	unsigned		number_num;

	number_num = 0;
	current += next_char(str, current);
	while (str[current] != 0 && str[current] != '\n')
	{
		al->data.vertex[current_vertex + (number_num++)] =
		(GLfloat)atof(str + current);

		if (str[current] == '-')
			++current;
		while (isdigit(str[current]) || str[current] == '.')
			current++;
		current += next_char(str, current);
		if (number_num > 3 || (str[current] != 0 && str[current] != '\n' &&
			str[current] != '-' && !isdigit(str[current])))
		{
			printf("Parsing error, invalid vertex (number %d)\n", number_num);
			yeet(al);
		}
	}
	if (number_num != 3)
	{
		printf("Parsing error, invalid vertex (%d numbers)\n", number_num);
		yeet(al);
	}


	al->data.vertex[current_vertex + 3] = color_palette[current_color++ % 6];
	// 0.2f + (rand() / (float)INT_MAX) * 0.8f;
	current_vertex += 4;
}

static void		parse_element(t_all *al, const char *str, size_t current)
{
	static unsigned	current_element = 0;
	GLuint			tmp[4];
	int				number_vertex;

	number_vertex = 0;
	current += next_char(str, current);
	while (str[current] != 0 && str[current] != '\n')
	{
		tmp[number_vertex++] = (GLuint)atoi(str + current);
		while (isdigit(str[current]))
			current++;
		current += next_char(str, current);
	}
	for (unsigned i = 0; i < 3; ++i)
		al->data.element[current_element + i] = tmp[i] - 1;
	current_element += 3;
	if (number_vertex == 4)
	{
		for (unsigned i = 0; i < 3; ++i)
			al->data.element[current_element + i] = tmp[(i + 2) % 4] - 1;
		current_element += 3;
	}
}

/* ########################################################################## */

/* to differenciate triangles from rectangle elements */
static size_t	element_type(const char *str, size_t current)
{
	int	number_vertex;

	number_vertex = 0;
	current += next_char(str, current);
	while (str[current] != 0 && str[current] != '\n')
	{
		++number_vertex;
		while (isdigit(str[current]))
			current++;
		if (str[current] == 0 || str[current] == ' ')
			current += next_char(str, current);
		else if (str[current] == '\n')
			break ;
		else
		{
			printf("Parsing error, invalid element [%c]\n", str[current]);
			exit(0);
		}
	}
	if (number_vertex != 3 && number_vertex != 4)
	{
		printf("Parsing error, invalid element (%d vertex)\n", number_vertex);
		exit(0);
	}
	return (number_vertex == 3 ? 1 : 2);
}

/* initialize vertex and element data sizes and malloc them */
static void		init_sizes(t_all *al, const char *str)
{
	size_t		current;

	current = 0;
	while (str[current])
	{
		switch (str[current])
		{
			case 'v' :
				++al->data.vertex_size;
				break ;
			case 'f' :
				al->data.element_size += element_type(str, current + 1);
				break ;
			case '#' :
			case 'm' :	/* mtllib */
			case 'o' :	/* o */
			case 's' :	/* s */
			case 'u' :	/* usemtl */
			case '\n' :
				break ;
			default :
				printf("Parsing error: invalid line >%c<\n", str[current]);
				yeet(al);
		}
		current += next_line(str, current);
	}
	al->data.vertex_size *= 4 * sizeof(float);
	al->data.element_size *= 3 * sizeof(unsigned int);
	al->data.vertex = malloc((size_t)al->data.vertex_size);
	al->data.element = malloc((size_t)al->data.element_size);
}

/* ########################################################################## */

void	parse_data(t_all *al, char *filename)
{
	const char	*file;
	size_t		current;
	
	file = read_file(filename);
	init_sizes(al, file);
	current = 0;
	while (file[current])
	{
		switch (file[current])
		{
			case 'v' :
				parse_vertex(al, file, current + 1);
				break ;
			case 'f' :
				parse_element(al, file, current + 1);
				break ;
			case '\n' :
				break ;
		}
		current += next_line(file, current);
	}
	free((void *)file);
	printf("Loaded %ld vertices and %ld elements\n",
		al->data.vertex_size / (long)(4 * sizeof(float)),
		al->data.element_size / (long)(3 * sizeof(unsigned int)));
}
