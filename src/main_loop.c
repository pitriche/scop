/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:47:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/05/31 13:47:15 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// static void	dtime(t_all *al)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, (void *)al->v0id);
// 	al->curr_time = tv.tv_sec * 1000000 + tv.tv_usec;
// 	if (al->curr_time < al->tgt_time)
// 	{
// 		usleep(al->tgt_time - al->curr_time);
// 		al->curr_time = al->tgt_time;
// 	}
// 	al->dtime = al->curr_time - al->last_time;
// 	al->dtime > 1000000 ? al->dtime = 1000000 : 0;
// 	al->last_time = al->curr_time;
// 	al->tgt_time = al->last_time + 1000000 / al->fps;
// }


void		key_func(t_all *al, SDL_Event *event)
{
	unsigned	value;

	value = event->type == SDL_KEYDOWN ? 1 : 0;
	switch (event->key.keysym.sym)
	{
		case (SDLK_ESCAPE) : yeet(al); break;
		case (SDLK_w) : al->keys.w = value; break;
		case (SDLK_a) : al->keys.a = value; break;
		case (SDLK_s) : al->keys.s = value; break;
		case (SDLK_d) : al->keys.d = value; break;
		case (SDLK_LEFT) : al->keys.left = value; break;
		case (SDLK_RIGHT) : al->keys.righ = value; break;
		case (SDLK_UP) : al->keys.up = value; break;
		case (SDLK_DOWN) : al->keys.down = value; break;
	}
}


void		main_loop(t_all *al)
{
	SDL_Event	event;

	while (1)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				yeet(al);
			if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) &&
				!event.key.repeat)
				key_func(al, &event);
		}
		al->pixels[10000] = 0xffff00;
		al->pixels[10001] = 0xffff00;
		al->pixels[10002] = 0xffff00;
		al->pixels[10003] = 0xff0000;
		al->pixels[10004] = 0xffff00;
		al->pixels[10005] = 0xffff00;
		al->pixels[10006] = 0xffff00;
		SDL_UpdateWindowSurface(al->window);
		// SDL_GL_SwapWindow(al->window); // or not
		// dtime(al);
	}
}
