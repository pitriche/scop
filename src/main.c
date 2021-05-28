/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:59:05 by becaraya          #+#    #+#             */
/*   Updated: 2021/05/28 18:25:52 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdlib.h> // exit

static void	init(t_all *al)
{
	//al->fps = 60;
	//al->total_pixel = this->res_x * this->res_y;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(0);
	if (!(al->window = SDL_CreateWindow(WIN_TITLE, WIN_POSX, WIN_POSY,
				WIN_SIZEX, WIN_SIZEY, SDL_WINDOW_SHOWN)))
		exit(0);
	if (!(al->surface = SDL_GetWindowSurface(al->window)))
		exit(0);
	al->pixels = al->surface->pixels;
}

#include <stdio.h>//////////
int			main(int argc, char **argv)
{
	t_all	al;

	//ft_bzero(&al, sizeof(t_all));
	if (argc == 2)
	{
		// if (read_n_pars(&al, argv[1]) == EXIT_FAILURE)
		// {
		// 	ft_putstr_fd("Invalid map\n", 2);
		// 	yeet(&al);
		// }
		init(&al);
		main_loop(&al);
	}
	return (0);
}
