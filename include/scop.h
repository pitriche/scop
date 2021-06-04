/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:59:52 by becaraya          #+#    #+#             */
/*   Updated: 2021/06/04 09:47:41 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/* fuck macos */
# define GL_SILENCE_DEPRECATION

// # include <math.h>
// # include <sys/time.h>
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
	SDL_GLContext	glcontext;

	SDL_Window		*window;
	// SDL_Surface	*surface;
	// unsigned int	*pixels;

	GLuint			vao; /* Vertex Array Object */
	
	GLuint			vbo; /* Vertex Buffer Object */

	t_shader		shader;
	t_attribute		attribute;
	t_uniform		uniform;

	t_keys			keys;
}				t_all;

/* ########################################################################## */

void	init(t_all *al);
void	main_loop(t_all *al);
void	render(t_all *al);
int		yeet(t_all *al);

#endif
