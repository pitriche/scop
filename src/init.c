/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 09:46:37 by brunomartin       #+#    #+#             */
/*   Updated: 2021/06/09 09:57:28 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "utils.h"		/* read_file, bzero, usec_timestamt */
#include <stdio.h>		/* printf */
#include <string.h>		/* bzero */

static void	init_time(t_time *time)
{
	time->fps = 60;
	time->last = usec_timestamp();
}

/* ########################################################################## */

static void	init_vao(t_all *al)
{
	glGenVertexArrays(1, &al->vao);
	glBindVertexArray(al->vao);
	printf("VAO: [%d/1]\t", al->vao);
}

static void	init_vbo(t_all *al)
{
	// static const GLfloat vertex[] =
	// {	/* position			|	color 				*/
	// 	-1.0f,	1.0f,	1.0f,	1.0f,	0.0f,	0.0f, /* nw */
	// 	1.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f, /* ne */
	// 	1.0f,	-1.0f,	1.0f,	1.0f,	0.0f,	0.0f, /* se */
	// 	-1.0f,	-1.0f,	1.0f,	0.0f,	0.0f,	1.0f, /* sw */
	// };

	glGenBuffers(1, &al->vbo);
	printf("VBO: [%d/1]\t", al->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, al->vbo);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, al->data.vertex_size, al->data.vertex,
		GL_STATIC_DRAW);
}

static void	init_ebo(t_all *al)
{
	// static const GLuint	element[] =
	// {
	// 	0, 1, 2, /* north east triangle */
	// 	2, 3, 0, /* south west triangle */
	// };

	glGenBuffers(1, &al->ebo);
	printf("EBO: [%d/2]\n", al->ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, al->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, al->data.element_size,
		al->data.element, GL_STATIC_DRAW);
}

/* ########################################################################## */

static GLuint compile_shader(const char *filename, GLenum type)
{
	GLuint	shader;
	char	*code;
	GLint	status;
	char	buffer[512];

	code = read_file(filename);
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, 0);

	/* compiling */
	glCompileShader(shader);
	
	/* error checking */
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		printf("[%s] shader compilation failed: [%d/1]\n", filename, status);
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		printf("Compilation log:\n%s\n", buffer);
		//yeet(al);
	}
	free(code);
	return (shader);
}

static void	init_shader(t_all *al)
{
	// char	buffer[512];
	// GLint	status[2] = {0, 0};

	// char * vertex_code;
	// char * fragment_code;

	// vertex_code = read_file("shader/vertex_shader.glsl");
	// fragment_code = read_file("shader/fragment_shader.glsl");
	// // al->shader.fragment_code = read_file("shader/geometry_shader.glsl");
	// al->shader.vertex = glCreateShader(GL_VERTEX_SHADER);
	// al->shader.fragment = glCreateShader(GL_FRAGMENT_SHADER);
	// glShaderSource(al->shader.vertex, 1, &vertex_code, 0);
	// glShaderSource(al->shader.fragment, 1, &fragment_code, 0);
	
	// /* compile shaders */
	// glCompileShader(al->shader.vertex);
	// glCompileShader(al->shader.fragment);

	// /* check shader compilation success */
	// glGetShaderiv(al->shader.vertex, GL_COMPILE_STATUS, &status[0]);
	// glGetShaderiv(al->shader.fragment, GL_COMPILE_STATUS, &status[1]);
	// if (status[0] != GL_TRUE || status[1] != GL_TRUE)
	// {
	// 	printf("Shaders compilation failed:\nvertex: [%d/1] fragment [%d/1]\n",
	// 		status[0], status[1]);
	// 	glGetShaderInfoLog(al->shader.vertex, 512, NULL, buffer);
	// 	printf("vertex log:\n%s\n", buffer);
	// 	glGetShaderInfoLog(al->shader.fragment, 512, NULL, buffer);
	// 	printf("fragment log:\n%s\n", buffer);
	// 	yeet(al);
	// }
	al->shader.vertex = compile_shader("shader/vertex_shader.glsl", GL_VERTEX_SHADER);
	al->shader.fragment = compile_shader("shader/fragment_shader.glsl", GL_FRAGMENT_SHADER);

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
	glVertexAttribPointer(al->attribute.position, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 4, (void *)(0));
	glEnableVertexAttribArray(al->attribute.position);
	
	al->attribute.color_grey = (GLuint)glGetAttribLocation(al->shader.program,
		"color_grey");
	glVertexAttribPointer(al->attribute.color_grey, 1, GL_FLOAT, GL_FALSE,
		sizeof(float) * 4, (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(al->attribute.color_grey);
}

static void	init_uniform(t_all *al)
{
	al->uniform.screen_ratio = glGetUniformLocation(al->shader.program,
		"screen_ratio");
	glUniform1f(al->uniform.screen_ratio, (GLfloat)WIN_SIZEX / WIN_SIZEY);


	al->uniform.model = glGetUniformLocation(al->shader.program,
		"model_matrix");
	glUniformMatrix4fv(al->uniform.model, 1, GL_FALSE, al->data.matrix.model);

	al->uniform.view = glGetUniformLocation(al->shader.program,
		"view_matrix");
	glUniformMatrix4fv(al->uniform.view, 1, GL_FALSE, al->data.matrix.view);
	
	al->uniform.projection = glGetUniformLocation(al->shader.program,
		"projection_matrix");
	glUniformMatrix4fv(al->uniform.projection, 1, GL_FALSE, al->data.matrix.projection);
}

/* ########################################################################## */

static void	init_matrix(t_all *al) // ADD MODEL BASED TRANSLATIONS
{
	set_mat4_identity(al->data.matrix.model);
	rotate_mat4(al->data.matrix.model, 0.0f, 0.0f, 0.1f);
	// print_mat4(al->data.matrix.model);
	translate_mat4(al->data.matrix.model, 0.0f, -1.0f, 0.0f);

	/* call translate before rotate */
	set_mat4_identity(al->data.matrix.view);
	translate_mat4(al->data.matrix.view, 0, 0, 5.5f);
	rotate_mat4(al->data.matrix.view, 0.0f, (float)M_PI, 0.0f);

	//print_mat4(al->data.matrix.view);


	set_mat4_projection(al->data.matrix.projection,
		(float)M_PI * CAMERA_FOV / 360.0f, CAMERA_NEAR, CAMERA_FAR,
		(float)WIN_SIZEX / WIN_SIZEY);

}

/* ########################################################################## */

void	init(t_all *al, char *filename)
{
	bzero(al, sizeof(t_all));

	/* init SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		yeet(al);

	/* init OpenGL context, version 4.1 (adapt version to OS supported) */
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,
			OPENGL_VERSION_MAJOR) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,
			OPENGL_VERSION_MINOR) < 0 ||
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) < 0)
		yeet(al);

	/* create window */
	if (!(al->window = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
				WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_OPENGL)))
		yeet(al);
	
	/* create OpenGL context */
	al->glcontext = SDL_GL_CreateContext(al->window);

	printf("Supported OpenGL version: %s\nUsing OpenGL %d.%d\n\n",
		glGetString(GL_VERSION), OPENGL_VERSION_MAJOR, OPENGL_VERSION_MINOR);

	parse_data(al, filename);
	// for (unsigned i = 0; i < al->data.element_size / sizeof(float) / 3; i ++)
	// 	printf("elem %d > %d %d %d\n", i, al->data.element[i*3+0], al->data.element[i*3+1], al->data.element[i*3+2]);
	init_vao(al);
	init_vbo(al);
	init_ebo(al);
	init_matrix(al);
	init_shader(al);
	init_attribute(al);
	init_uniform(al);
	glEnable(GL_DEPTH_TEST);

	init_time(&al->time);
}
