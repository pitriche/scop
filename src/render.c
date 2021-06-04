/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:38:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/04 10:51:36 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	render(t_all *al)
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(al->window);

	// al->pixels[10000] = 0xffffff;
	// al->pixels[10001] = 0xffffff;
	// al->pixels[10002] = 0xffffff;
	// SDL_UpdateWindowSurface(al->window);
}
