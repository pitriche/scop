/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 09:43:00 by brunomartin       #+#    #+#             */
/*   Updated: 2021/06/04 12:32:11 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>		/* printf */

int			main(int argc, char **argv)
{
	t_all	al;

	if (argc == 2)
	{
		init(&al, argv[1]);
		main_loop(&al);
	}
	printf("Usage: ./scop filename\n");
	return (0);
}
