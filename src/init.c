/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre42 <pierre42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 09:46:37 by brunomartin       #+#    #+#             */
/*   Updated: 2021/06/09 17:58:47 by pierre42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "utils.h"		/* read_file, bzero, usec_timestamt */
#include "matrix.h"		/* translate_mat4 */
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
	glGenBuffers(1, &al->vbo);
	printf("VBO: [%d/1]\t", al->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, al->vbo);
	glBufferData(GL_ARRAY_BUFFER, al->data.vertex_size, al->data.vertex,
		GL_STATIC_DRAW);
}

static void	init_ebo(t_all *al)
{
	glGenBuffers(1, &al->ebo);
	printf("EBO: [%d/2]\n", al->ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, al->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, al->data.element_size,
		al->data.element, GL_STATIC_DRAW);
}

/* ########################################################################## */

static GLuint compile_shader(t_all *al, const char *filename, GLenum type)
{
	GLuint		shader;
	const char	*code;
	GLint		status;
	char		buffer[512];

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
		yeet(al);
	}
	free((void *)code);
	return (shader);
}

static void	init_shader(t_all *al)
{
	al->shader.vertex = compile_shader(al, "shader/vertex_shader.glsl",
		GL_VERTEX_SHADER);
	al->shader.geometry = compile_shader(al, "shader/geometry_shader.glsl",
		GL_GEOMETRY_SHADER);
	al->shader.fragment = compile_shader(al, "shader/fragment_shader.glsl",
		GL_FRAGMENT_SHADER);

	/* create shader program and attach shaders */
	al->shader.program = glCreateProgram();
	printf("Program: [%d/4]\n", al->shader.program);
	glAttachShader(al->shader.program, al->shader.vertex);
	glAttachShader(al->shader.program, al->shader.geometry);
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
	/* matrices */
	al->uniform.model = glGetUniformLocation(al->shader.program,
		"model_matrix");
	glUniformMatrix4fv(al->uniform.model, 1, GL_FALSE, al->data.matrix.model);

	al->uniform.view = glGetUniformLocation(al->shader.program,
		"view_matrix");
	glUniformMatrix4fv(al->uniform.view, 1, GL_FALSE, al->data.matrix.view);
	
	al->uniform.projection = glGetUniformLocation(al->shader.program,
		"projection_matrix");
	glUniformMatrix4fv(al->uniform.projection, 1, GL_FALSE,
		al->data.matrix.projection);

	/* color blending between texture and facet */
	al->data.blending = 0.0;
	al->data.animation_status = 0;
	al->uniform.blending = glGetUniformLocation(al->shader.program,
		"blending");
	glUniform1f(al->uniform.blending, al->data.blending);
}

/* ########################################################################## */

static void	init_matrix(t_all *al)
{
	set_mat4_identity(al->data.matrix.model);

	/* set the camera to face positive Z and stand back */
	set_mat4_identity(al->data.matrix.view);
	rotate_mat4(al->data.matrix.view, 0.0f, (float)M_PI, 0.0f);
	translate_mat4(al->data.matrix.view, 0, 0, -4.5f);

	set_mat4_projection(al->data.matrix.projection,
		(float)M_PI * CAMERA_FOV / 360.0f, CAMERA_NEAR, CAMERA_FAR,
		(float)WIN_SIZEX / WIN_SIZEY);
}

/* ########################################################################## */

static void		init_texture(t_all *al)
{
	float	*pixels;

	glGenTextures(1, &al->texture);
	glBindTexture(GL_TEXTURE_2D, al->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	pixels = load_bmp("texture.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1200, 675, 0, GL_RGB, GL_FLOAT,
		pixels);
	free(pixels);
}

/* ########################################################################## */

static void	center_model(t_all *al)
{
	float	tmpx;
	float	tmpy;
	float	tmpz;
	/* XYZ min and max */
	float	min[3] = {INFINITY, INFINITY, INFINITY};
	float	max[3] = {-INFINITY, -INFINITY, -INFINITY};

	for (unsigned i = 0; i < (unsigned)al->data.vertex_size /
		(4 * sizeof(float)); ++i)
	{
		tmpx = al->data.vertex[i * 4 + 0];
		tmpy = al->data.vertex[i * 4 + 1];
		tmpz = al->data.vertex[i * 4 + 2];

		if (tmpx < min[0])
			min[0] = tmpx;
		if (tmpx > max[0])
			max[0] = tmpx;
		if (tmpy < min[1])
			min[1] = tmpy;
		if (tmpy > max[1])
			max[1] = tmpy;
		if (tmpz < min[2])
			min[2] = tmpz;
		if (tmpz > max[2])
			max[2] = tmpz;
	}
	translate_mat4(al->data.matrix.model, -(min[0] + max[0]) / 2.0f, 0, 0);
	translate_mat4(al->data.matrix.model, 0, -(min[1] + max[1]) / 2.0f, 0);
	translate_mat4(al->data.matrix.model, 0, 0, -(min[2] + max[2]) / 2.0f);
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
	init_vao(al);
	init_vbo(al);
	init_ebo(al);
	init_matrix(al);
	init_shader(al);
	init_attribute(al);
	init_uniform(al);
	init_texture(al);
	center_model(al);
	glEnable(GL_DEPTH_TEST);

	init_time(&al->time);
}
