/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:59:52 by becaraya          #+#    #+#             */
/*   Updated: 2021/06/04 17:42:02 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/* fuck macos */
# define GL_SILENCE_DEPRECATION

# include <OpenGL/gl3.h>
# include "SDL.h"

# define WIN_TITLE "xXx_Qu1Ck_Sc0P_xXx"
# define WIN_SIZEX	1280
# define WIN_SIZEY	720
# define WIN_POSX	100
# define WIN_POSY	50

/* ########################################################################## */

typedef struct	s_keys
{
	unsigned	w:1;
	unsigned	a:1;
	unsigned	s:1;
	unsigned	d:1;
	unsigned	left:1;
	unsigned	righ:1;
	unsigned	up:1;
	unsigned	down:1;
}				t_keys;

/* ########################################################################## */

typedef struct	s_time
{
	unsigned		fps;

	/* usec timestamps */
	unsigned long	current;
	unsigned long	last;
	unsigned long	target;
	unsigned long	delta;

	unsigned long	elapsed; /* can lag behind real time if frame time >1sec */
	unsigned		elapsed_frames;
}				t_time;

/* ########################################################################## */

/* 3d data and buffers */
typedef struct	s_data
{
	GLsizeiptr	vertex_size;
	GLfloat		*vertex;

	GLsizeiptr	element_size;
	GLuint		*element;
}				t_data;

typedef struct	s_uniform
{
	GLint	screen_ratio;
}				t_uniform;

typedef struct	s_attribute
{
	GLuint	position;
	GLuint	color;
}				t_attribute;

typedef struct	s_shader
{
	const GLchar	*vertex_code;
	const GLchar	*fragment_code;

	GLuint 			vertex;
	GLuint 			fragment;

	GLuint			program;
}				t_shader;

/* ########################################################################## */

typedef struct	s_all
{
	/* SDL */
	SDL_Window		*window;
	SDL_GLContext	glcontext;
	// SDL_Surface	*surface;
	// unsigned int	*pixels;

	/* OpenGL */
	GLuint			vao; /* Vertex Array Object */
	GLuint			vbo; /* Vertex Buffer Object */
	GLuint			ebo; /* Element Buffer Object */
	t_shader		shader;
	t_attribute		attribute;
	t_uniform		uniform;

	t_data			data;

	t_time			time;
	t_keys			keys;
}				t_all;

/* ########################################################################## */

void	init(t_all *al, char *filename);
void	parse_data(t_all *al, char *filename);
void	main_loop(t_all *al);
void	render(t_all *al);
int		yeet(t_all *al);

#endif
