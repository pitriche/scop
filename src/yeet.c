/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/02 15:04:25 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	yeet(t_all *al)
{
	/* shaders code */
	if (al->shader.fragment_code)
		free((void *)al->shader.fragment_code);
	if (al->shader.vertex_code)
		free((void *)al->shader.vertex_code);

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
