/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre42 <pierre42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:47:13 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/09 17:07:44 by pierre42         ###   ########.fr       */
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
	al->time.delta_sec = al->time.delta / 1000000.0f;

	al->time.last = al->time.current;
	al->time.target = al->time.current + 1000000 / al->time.fps;

	al->time.elapsed += al->time.delta;
	++al->time.elapsed_frames;
}

static void	key_func(t_all *al, SDL_Event *event)
{
	unsigned	value;

	if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_c)
		al->data.animation_status = !al->data.animation_status;
	value = event->type == SDL_KEYDOWN ? 1 : 0;
	switch (event->key.keysym.sym)
	{
		case (SDLK_ESCAPE) : yeet(al); break;
		case (SDLK_w) : al->keys.w = value; break;
		case (SDLK_a) : al->keys.a = value; break;
		case (SDLK_s) : al->keys.s = value; break;
		case (SDLK_d) : al->keys.d = value; break;
		case (SDLK_z) : al->keys.z = value; break;
		case (SDLK_x) : al->keys.x = value; break;
	}
}

static void	update(t_all *al)
{
	rotate_mat4(al->data.matrix.model, 0.0f, al->time.delta_sec * 0.7f, 0.0f);

	if (al->keys.w)
		translate_mat4(al->data.matrix.view, 0, al->time.delta_sec * 2, 0);
	if (al->keys.a)
		translate_mat4(al->data.matrix.view, -al->time.delta_sec * 2, 0, 0);
	if (al->keys.s)
		translate_mat4(al->data.matrix.view, 0, -al->time.delta_sec * 2, 0);
	if (al->keys.d)
		translate_mat4(al->data.matrix.view, al->time.delta_sec * 2, 0, 0);
	if (al->keys.z)
		translate_mat4(al->data.matrix.view, 0, 0, -al->time.delta_sec * 2);
	if (al->keys.x)
		translate_mat4(al->data.matrix.view, 0, 0, al->time.delta_sec * 2);

	if (al->data.animation_status)
	{
		if (al->data.blending < 1.0f)
			al->data.blending += al->time.delta_sec * 0.8f;
	}
	else
	{
		if (al->data.blending > 0.0f)
			al->data.blending -= al->time.delta_sec * 0.8f;
	}

	/* update uniforms */
	glUniformMatrix4fv(al->uniform.model, 1, GL_FALSE, al->data.matrix.model);
	glUniformMatrix4fv(al->uniform.view, 1, GL_FALSE, al->data.matrix.view);
	glUniform1f(al->uniform.blending, al->data.blending);
	
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

		update(al);
		render(al);
		dtime(al);
		if (al->time.elapsed_frames % 30 == 0)
			//printf("Render time: %f ms\n", al->time.delta / 1000.0f);
			printf("FPS : %lu\n", 1000000 / al->time.delta);
	}
}
