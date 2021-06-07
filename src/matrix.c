/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:11:33 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/07 15:18:07 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "utils.h"
#include <stdio.h>		/* printf */

void	set_mat4_identity(mat4 mat)
{
	ft_bzero(mat, 16 * sizeof(float));
	mat[0] = 1.0f;
	mat[5] = 1.0f;
	mat[10] = 1.0f;
	mat[15] = 1.0f;
}

void	print_mat4(mat4 mat)
{
	for (unsigned i = 0; i < 16; i += 4)
		printf("%8f|%8f|%8f|%8f\n", mat[0 + i], mat[1 + i], mat[2 + i],
			mat[3 + i]);
}