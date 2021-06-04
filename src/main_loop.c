/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:47:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/04 10:41:55 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "utils.h"	/* usec_timestamp */
#include <unistd.h>	/* usleep */

static void	dtime(t_all *al)
{
	al->time.current = usec_timestamp();

	if (al->time.current < al->time.target)
	{
		usleep((unsigned int)(al->time.target - al->time.current));
		al->time.current = al->time.target;
	}

	al->time.delta = al->time.current - al->time.last;
	al->time.delta > 1000000 ? al->time.delta = 1000000 : 0;

	al->time.last = al->time.current;
	al->time.target = al->time.current + 1000000 / al->time.fps;

	al->time.elapsed += al->time.delta;
	++al->time.elapsed_frames;
}

static void	key_func(t_all *al, SDL_Event *event)
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
		render(al);

		dtime(al);
		if (al->time.elapsed_frames % 30 == 0)
			//printf("Render time: %f ms\n", al->time.delta / 1000.0f);
			printf("FPS : %lu\n", 1000000 / al->time.delta);
	}
}
