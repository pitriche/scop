/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:59:05 by becaraya          #+#    #+#             */
/*   Updated: 2021/06/02 15:15:42 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "utils.h"
#include <stdlib.h>		// exit, malloc
#include <stdio.h>		// printf

static void	init(t_all *al)
{
	//al->fps = 60;
	//al->total_pixel = this->res_x * this->res_y;
	
	/* init SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(0);

	/* init OpenGL context */
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) < 0)
		yeet(al);

	/* create window */
	if (!(al->window = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
				WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_OPENGL)))
		yeet(al);
	
	/* create OpenGL context and fetch functions */
	al->glcontext = SDL_GL_CreateContext(al->window);

	/* fetch window surface and pixels */
	// if (!(al->surface = SDL_GetWindowSurface(al->window)))
	// 	yeet(al);
	// al->pixels = al->surface->pixels;
}

static void	init_vbo(t_all *al)
{
	static const GLfloat vertex[9] =
	{
		-1.0f,	-1.0f,	0.0f,
		1.0f,	-1.0f,	0.0f,
		0.0f,	1.0f,	0.0f,
	};
	glGenBuffersARB(1, &al->vbo);

	glBindBufferARB(GL_ARRAY_BUFFER, al->vbo);
	glBufferDataARB(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

}

static void	init_shader(t_all *al)
{
	GLint status[2];

	al->shader.vertex_code = read_file("shader/vertex_shader.glsl");
	al->shader.fragment_code = read_file("shader/fragment_shader.glsl");
	al->shader.vertex = glCreateShader(GL_VERTEX_SHADER);
	al->shader.fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(al->shader.vertex, 1, &al->shader.vertex_code, 0);
	glShaderSource(al->shader.fragment, 1, &al->shader.fragment_code, 0);
	
	/* compile shaders */
	glCompileShader(al->shader.vertex);
	glCompileShader(al->shader.fragment);

	/* check shader compilation success */
	glGetShaderiv(al->shader.vertex, GL_COMPILE_STATUS, &status[0]);
	glGetShaderiv(al->shader.fragment, GL_COMPILE_STATUS, &status[1]);
	if (status[0] != GL_TRUE || status[1] != GL_TRUE)
	{
		printf("Shaders compilation failed\n");
		yeet(al);
	}

	/* create shader program and attach shaders */
	al->shader.program = glCreateProgram();
	glAttachShader(al->shader.program, al->shader.vertex);
	glAttachShader(al->shader.program, al->shader.fragment);
	glBindFragDataLocationEXT(al->shader.program, 0, "outColor");

	/* link and use shader program */
	glLinkProgram(al->shader.program);
	glUseProgram(al->shader.program);
}

static void	init_pointers(t_all *al)
{
	GLuint posAttrib;
	
	posAttrib = (GLuint)glGetAttribLocation(al->shader.program, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	// to complete
}

/* ########################################################################## */

int			main(int argc, char **argv)
{
	t_all	al;

	(void)argv;
	ft_bzero(&al, sizeof(t_all));
	if (argc == 2)
	{
		init(&al);
		init_vbo(&al);
		init_shader(&al);
		init_pointers(&al);
		main_loop(&al);
	}
	return (0);
}
