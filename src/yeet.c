/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/04 12:24:40 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

int	yeet(t_all *al)
{
	/* shaders code */
	if (al->shader.fragment_code)
		free((void *)al->shader.fragment_code);
	if (al->shader.vertex_code)
		free((void *)al->shader.vertex_code);

	
	/* vertex and element data */
	if (al->data.vertex)
		free((void *)al->data.vertex);
	if (al->data.element)
		free((void *)al->data.element);

	/* OpenGL Context */
	if (al->glcontext)
		SDL_GL_DeleteContext(al->glcontext);

	/* SDL window and SDL */
	if (al->window)
	{
		SDL_DestroyWindow(al->window);
		SDL_Quit();
	}
	exit(0);
}
