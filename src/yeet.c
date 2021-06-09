/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/09 09:52:37 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h>

int	yeet(t_all *al)
{
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
