/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:38:54 by pitriche          #+#    #+#             */
/*   Updated: 2019/08/20 15:23:55 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	wall_ver(t_all *al, double ang)
{
	int		x;
	int		fck;
	double	tmp;

	x = al->play.posx;
	tmp = 1 / tan(ang);
	fck = ang < M_PI ? 0 : 1;
	while (fck ? (x >= 0) : (++x < al->x_mx_map))
	{
		al->hit_nesw = fck ? 1 : 3;
		al->hitx = x;
		al->hity = al->play.posy + (x - al->play.posx) * tmp;
		al->hperc = fck ? 1 + (int)al->hity - al->hity :
		al->hity - (int)al->hity;
		al->hitdst = ((x - al->play.posx) / sin(ang)) * cos(ang -
			al->play.dir);
		al->hity > 0 && al->hity <= al->y_mx_map ? al->hit =
			al->map[(int)al->hity][(int)al->hitx - fck] : 0;
		if (al->hit)
			return ;
		fck ? x-- : 0;
	}
}

static void	wall_hor(t_all *al, double ang)
{
	int		y;
	int		fck;
	double	tmp;

	y = al->play.posy;
	tmp = tan(ang);
	fck = ang < M_PI / 2 || ang > 3 * M_PI / 2 ? 0 : 1;
	while (fck ? (y >= 0) : (++y < al->y_mx_map))
	{
		al->hhit_ns = fck ? 2 : 0;
		al->hhity = y;
		al->hhitx = al->play.posx + (y - al->play.posy) * tmp;
		al->hhperc = !fck ? 1 + (int)al->hhitx - al->hhitx :
		al->hhitx - (int)al->hhitx;
		al->hhitdst = ((y - al->play.posy) / cos(ang)) * cos(ang -
			al->play.dir);
		al->hhitx > 0 && al->hhitx <= al->x_mx_map ? al->hhit =
			al->map[(int)al->hhity - fck][(int)al->hhitx] : 0;
		if (al->hhit)
			return ;
		fck ? y-- : 0;
	}
}

void		cast_ray(t_all *al, int x)
{
	double	ang;

	al->hhit = 0;
	al->hit = 0;
	ang = al->play.dir + al->play.fov * ((1 - (x / (double)WIN_SIZEX)) - 0.5);
	while (ang > M_2PI)
		ang -= M_2PI;
	while (ang < 0)
		ang += M_2PI;
	wall_ver(al, ang);
	wall_hor(al, ang);
	if (!al->hhit)
		return ;
	if (!al->hit || al->hitdst > al->hhitdst)
	{
		al->hit = al->hhit;
		al->hit_nesw = al->hhit_ns;
		al->hperc = al->hhperc;
		al->hitx = al->hhitx;
		al->hity = al->hhity;
		al->hitdst = al->hhitdst;
	}
}

void		render(t_all *al)
{
	int		x;

	x = 0;
	while (x < WIN_SIZEX)
	{
		cast_ray(al, x);
		column(al, x, al->hitdst);
		x++;
	}
	minimap(al);
	if (al->status == ST_GAME)
	{
		SDL_UpdateTexture(al->tex, 0, al->pix, WIN_SIZEX * sizeof(int));
		SDL_RenderCopy(al->ren, al->tex, 0, 0);
		SDL_RenderPresent(al->ren);
	}
}
