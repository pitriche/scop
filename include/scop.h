/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre42 <pierre42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:59:52 by becaraya          #+#    #+#             */
/*   Updated: 2021/06/09 17:56:57 by pierre42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/* fuck macos */
# define GL_SILENCE_DEPRECATION

# include <OpenGL/gl3.h>
# include "SDL.h"

# include "matrix.h"

# define OPENGL_VERSION_MAJOR	4
# define OPENGL_VERSION_MINOR	1

# define WIN_TITLE "xXx_Qu1Ck_Sc0P_xXx"
# define WIN_SIZEX	1280
# define WIN_SIZEY	720
# define WIN_POSX	100
# define WIN_POSY	50

# define CAMERA_FOV		60.0f
# define CAMERA_NEAR	1.0f
# define CAMERA_FAR		10.0f


/* ########################################################################## */

typedef struct	s_keys
{
	unsigned	w:1;
	unsigned	a:1;
	unsigned	s:1;
	unsigned	d:1;
	unsigned	z:1;
	unsigned	x:1;
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
	float			delta_sec;

	unsigned long	elapsed; /* can lag behind real time if frame time >1sec */
	unsigned long	elapsed_frames;
}				t_time;

/* ########################################################################## */

typedef struct	s_matrix
{
	mat4	model;
	mat4	view;
	mat4	projection;
}				t_matrix;

/* 3d data and buffers */
typedef struct	s_data
{
	float		fov;		/* radiant fov */

	float		blending;	/* blend facet and texture colors */
	unsigned	animation_status;


	t_matrix	matrix;

	GLsizeiptr	vertex_size;
	GLfloat		*vertex;

	GLsizeiptr	element_size;
	GLuint		*element;
}				t_data;

typedef struct	s_uniform
{
	/* matrices */
	GLint	model;
	GLint	view;
	GLint	projection;

	GLint	blending;
}				t_uniform;

typedef struct	s_attribute
{
	GLuint	position;
	GLuint	color_grey;
}				t_attribute;

typedef struct	s_shader
{
	GLuint 			vertex;
	GLuint 			geometry;
	GLuint 			fragment;

	GLuint			program;
}				t_shader;

/* ########################################################################## */

typedef struct	s_all
{
	/* SDL */
	SDL_Window		*window;
	SDL_GLContext	glcontext;

	/* OpenGL */
	GLuint			vao; /* Vertex Array Object */
	GLuint			vbo; /* Vertex Buffer Object */
	GLuint			ebo; /* Element Buffer Object */
	t_shader		shader;
	t_attribute		attribute;
	t_uniform		uniform;

	GLuint 			texture;

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
