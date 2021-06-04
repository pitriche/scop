/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 09:46:37 by brunomartin       #+#    #+#             */
/*   Updated: 2021/06/04 09:59:06 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"		/* t_all */
#include "utils.h"		/* read_file, bzero */
#include <stdio.h>		/* printf */

static void	init_vao(t_all *al)
{
	glGenVertexArrays(1, &al->vao);
	glBindVertexArray(al->vao);
	printf("VAO: [%d/1]\n", al->vao);
}

static void	init_vbo(t_all *al)
{
	static const GLfloat vertex[] =
	{	/* position				|	color 				*/
		-1.0f,	-0.866f,	1.0f,	1.0f,	0.0f,	0.0f,
		1.0f,	-0.866f,	1.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.866f,		1.0f,	0.0f,	0.0f,	1.0f,
	};
	glGenBuffers(1, &al->vbo);
	printf("VBO: [%d/1]\n", al->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, al->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
}

/* ########################################################################## */

static void	init_shader(t_all *al)
{
	GLint status[2] = {0, 0};

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
		printf("Shaders compilation failed:\nvertex: [%d/1] fragment [%d/1]\n",
			al->shader.vertex, al->shader.fragment);
		yeet(al);
	}

	/* create shader program and attach shaders */
	al->shader.program = glCreateProgram();
	printf("Program: [%d/3]\n", al->shader.program);
	glAttachShader(al->shader.program, al->shader.vertex);
	glAttachShader(al->shader.program, al->shader.fragment);
	glBindFragDataLocation(al->shader.program, 0, "outColor");

	/* link and use shader program */
	glLinkProgram(al->shader.program);
	glUseProgram(al->shader.program);
}

/* ########################################################################## */

static void	init_attribute(t_all *al)
{
	al->attribute.position = (GLuint)glGetAttribLocation(al->shader.program,
		"position");
	al->attribute.color = (GLuint)glGetAttribLocation(al->shader.program,
		"color");
	
	glVertexAttribPointer(al->attribute.position, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 6, (void *)(0));
	glVertexAttribPointer(al->attribute.color, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 6, (void *)(sizeof(float) * 3));
	
	glEnableVertexAttribArray(al->attribute.position);
	glEnableVertexAttribArray(al->attribute.color);
}

static void	init_uniforms(t_all *al)
{
	al->uniform.screen_ratio = glGetUniformLocation(al->shader.program,
		"screen_ratio");
	glUniform1f(al->uniform.screen_ratio, (GLfloat)WIN_SIZEX / WIN_SIZEY);
	// to complete
}

/* ########################################################################## */

void	init(t_all *al)
{
	ft_bzero(al, sizeof(t_all));

	//al->fps = 60;

	/* init SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);

	/* init OpenGL context, version 4.1 (adapt version to OS supported) */
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) < 0)
		yeet(al);

	/* create window */
	if (!(al->window = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
				WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_OPENGL)))
		yeet(al);
	
	/* create OpenGL context */
	al->glcontext = SDL_GL_CreateContext(al->window);

	/* fetch window surface and pixels, DON'T USE ALONGSIDE OPENGL */
	// if (!(al->surface = SDL_GetWindowSurface(al->window)))
	// 	yeet(al);
	// al->pixels = al->surface->pixels;

	init_vao(al);
	init_vbo(al);
	init_shader(al);
	init_attribute(al);
	init_uniforms(al);
}
