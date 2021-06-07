/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 09:43:00 by brunomartin       #+#    #+#             */
/*   Updated: 2021/06/07 15:15:15 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>		/* printf */

#include "matrix.h" ////////////////////////////

int			main(int argc, char **argv)
{
	t_all	al;

	mat4 mat;

	print_mat4(mat);
	write(1, "\n", 1);
	set_mat4_identity(mat);
	print_mat4(mat);
	
	if (argc == 2)
	{
		init(&al, argv[1]);
		main_loop(&al);
	}
	printf("Usage: ./scop filename\n");
	return (0);
}
