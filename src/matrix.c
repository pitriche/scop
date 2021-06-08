/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:11:33 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/08 16:39:11 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "utils.h"
#include <stdio.h>	/* printf */
#include <math.h>	/* cos, sin */
#include <string.h>	/* memcpy */

void	print_mat4(mat4 mat)
{
	for (unsigned i = 0; i < 16; i += 4)
		printf("%8f|%8f|%8f|%8f\n", mat[0 + i], mat[1 + i], mat[2 + i],
			mat[3 + i]);
}

void	set_mat4_identity(mat4 mat)
{
	bzero(mat, 16 * sizeof(float));
	mat[0] = 1.0f;
	mat[5] = 1.0f;
	mat[10] = 1.0f;
	mat[15] = 1.0f;
}

void	translate_mat4(mat4 mat, float x, float y, float z)
{
	/* WHY IS THIS NOT WORKING */
	// mat[3] += x;
	// mat[7] += y;
	// mat[11] += z;

	mat[12] += x;
	mat[13] += y;
	mat[14] += z;
}

/* multiply matrices, store result in mat_a */
void	multiply_mat4(mat4 mat_a, mat4 mat_b)
{
	mat4	res;

	for (unsigned j = 0; j < 4; ++j)
		for (unsigned i = 0; i < 4; ++i)
		{
			res[j * 4 + i] =
			mat_a[j * 4 + 0] * mat_b[0 * 4 + i] +
			mat_a[j * 4 + 1] * mat_b[1 * 4 + i] +
			mat_a[j * 4 + 2] * mat_b[2 * 4 + i] +
			mat_a[j * 4 + 3] * mat_b[3 * 4 + i];
		}
	memcpy(mat_a, res, sizeof(mat4));
}

/* ########################################################################## */

/*	1  0  0  0
	0  C -S  0
	0  S  C  0
	0  0  0  1 */
void	set_rotate_x_mat4(mat4 mat, float x) //
{
	set_mat4_identity(mat);
	mat[5] = cosf(x);
	mat[6] = -sinf(x);
	mat[9] = sinf(x);
	mat[10] = cosf(x);
}

/*	C  0  S  0
	0  1  0  0
	-S 0  C  0
	0  0  0  1 */
void	set_rotate_y_mat4(mat4 mat, float y) //
{
	set_mat4_identity(mat);
	mat[0] = cosf(y);
	mat[2] = sinf(y);
	mat[8] = -sinf(y);
	mat[10] = cosf(y);
}

/*	C -S  0  0
	S  C  0  0
	0  0  1  0
	0  0  0  1 */
void	set_rotate_z_mat4(mat4 mat, float z) //
{
	set_mat4_identity(mat);
	mat[0] = cosf(z);
	mat[1] = -sinf(z);
	mat[4] = sinf(z);
	mat[5] = cosf(z);
}

/* x: pitch, y:yaw, z:roll, applied yaw->pitch->roll in relative coordonates */
void	rotate_mat4(mat4 mat, float x, float y, float z)
{
	mat4 rot_x;
	mat4 rot_y;
	mat4 rot_z;

	set_rotate_x_mat4(rot_x, x);
	set_rotate_y_mat4(rot_y, y);
	set_rotate_z_mat4(rot_z, z);

	/* Z * X * Y */
	multiply_mat4(rot_z, rot_x);
	multiply_mat4(rot_z, rot_y);
	
	multiply_mat4(mat, rot_z);
}

/* ########################################################################## */

void	set_mat4_projection(mat4 mat, float fov, float near, float far,
	float aspect)
{
	float	e;

	e = 1 / (tanf(fov / 2.0f));
	mat[0] = e / aspect;
	mat[5] = e;
	mat[10] = (near + far) / (near - far);
	mat[11] = (2 * near * far) / (near - far);
	mat[14] = -1;
}