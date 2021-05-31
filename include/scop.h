/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:59:52 by becaraya          #+#    #+#             */
/*   Updated: 2021/05/31 15:27:20 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

// # include <math.h>
// # include <sys/time.h>
# include <OpenGL/glext.h>
# include "SDL.h"

# define WIN_TITLE "xXx_Qu1Ck_Sc0P_xXx"
# define WIN_SIZEX 1280
# define WIN_SIZEY 720
# define WIN_POSX 100
# define WIN_POSY 50

/* ########################################################################## */

typedef struct	s_keys
{
	unsigned	w:1;
	unsigned	a:1;
	unsigned	s:1;
	unsigned	d:1;
	unsigned	left:1;
	unsigned	righ:1;
	unsigned	up:1;
	unsigned	down:1;
}				t_keys;

/* ########################################################################## */

typedef void	(*GENBUFFERS) (GLsizei, GLuint*);

typedef struct	s_GLfunction
{
	GENBUFFERS	glGenBuffers;
}				t_GLfunction;

/* ########################################################################## */

typedef struct	s_all
{
	SDL_GLContext	glcontext;

	SDL_Window		*window;
	SDL_Surface		*surface;
	unsigned int	*pixels;

	t_keys			keys;
	t_GLfunction	gl;
}				t_all;

/* ########################################################################## */

void	main_loop(t_all *al);
int		yeet(t_all *al);

#endif
