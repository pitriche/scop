/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre42 <pierre42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:38:54 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/09 17:59:29 by pierre42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	render(t_all *al)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glDrawElements(GL_TRIANGLES, (GLsizei)al->data.element_size /
		(GLsizei)sizeof(float), GL_UNSIGNED_INT, 0);

	SDL_GL_SwapWindow(al->window);
}
