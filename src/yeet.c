/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeet.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:23:57 by pitriche          #+#    #+#             */
/*   Updated: 2021/05/31 11:36:03 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int	yeet(t_all *al)
{
	if (al->glcontext)
		SDL_GL_DeleteContext(al->glcontext);
	if (al->window)
	{
		SDL_DestroyWindow(al->window);
		SDL_Quit();
	}
	exit(0);
}
