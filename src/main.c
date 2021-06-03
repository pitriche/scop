/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:59:05 by becaraya          #+#    #+#             */
/*   Updated: 2021/06/01 10:26:43 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "utils.h"
#include <stdlib.h>			// exit
#include <mach-o/dyld.h>	// NSLookupAndBindSymbol, NSAddressOfSymbol
#include <stdlib.h>			// malloc

/* requires an _ before the name (ex. "_glGenBuffers") */
void	*GetProcAddress(const char *name)
{
	NSSymbol	symbol;

	symbol = 0;
	if (NSIsSymbolNameDefined(name))
		symbol = NSLookupAndBindSymbol(name);
	return (symbol ? NSAddressOfSymbol(symbol) : 0);
}

static void	_openGl_function_load(t_GLfunction *func)
{
	func->glGenBuffers = (GENBUFFERS)GetProcAddress("_glGenBuffers");
}

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
	_openGl_function_load(&al->gl);

	/* fetch window surface and pixels */
	if (!(al->surface = SDL_GetWindowSurface(al->window)))
		yeet(al);
	al->pixels = al->surface->pixels;

	GLuint buffer;
	al->gl.glGenBuffers(1, &buffer);
}

int			main(int argc, char **argv)
{
	t_all	al;

	ft_bzero(&al, sizeof(t_all));
	if (argc == 2)
	{
		init(&al);
		main_loop(&al);
	}
	return (0);
}
