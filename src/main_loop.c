/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:47:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/05/28 18:33:17 by pitriche         ###   ########.fr       */
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
	SDL_KeyboardEvent kev;

	kev = event->key;
	if (event->type == SDL_KEYDOWN)
	{
		kev.keysym.sym == SDLK_ESCAPE ? exit(0) : 0;
		kev.keysym.sym == SDLK_w ? al->keys.w = 1 : 0;
		kev.keysym.sym == SDLK_a ? al->keys.a = 1 : 0;
		kev.keysym.sym == SDLK_s ? al->keys.s = 1 : 0;
		kev.keysym.sym == SDLK_d ? al->keys.d = 1 : 0;
		kev.keysym.sym == SDLK_LEFT ? al->keys.left = 1 : 0;
		kev.keysym.sym == SDLK_RIGHT ? al->keys.righ = 1 : 0;
		kev.keysym.sym == SDLK_UP ? al->keys.up = 1 : 0;
		kev.keysym.sym == SDLK_DOWN ? al->keys.down = 1 : 0;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		kev.keysym.sym == SDLK_w ? al->keys.w = 0 : 0;
		kev.keysym.sym == SDLK_a ? al->keys.a = 0 : 0;
		kev.keysym.sym == SDLK_s ? al->keys.s = 0 : 0;
		kev.keysym.sym == SDLK_d ? al->keys.d = 0 : 0;
		kev.keysym.sym == SDLK_LEFT ? al->keys.left = 0 : 0;
		kev.keysym.sym == SDLK_RIGHT ? al->keys.righ = 0 : 0;
		kev.keysym.sym == SDLK_UP ? al->keys.up = 0 : 0;
		kev.keysym.sym == SDLK_DOWN ? al->keys.down = 0 : 0;
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
				exit(0);
			if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) &&
				!event.key.repeat)
				key_func(al, &event);
		}
		// dtime(al);
		// if (al->status == ST_GAME)
		// 	game(al);
		// if (al->status == ST_PAUSE)
		// 	game_pause(al);
	}
}
