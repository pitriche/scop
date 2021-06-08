/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:12:27 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/08 12:58:16 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef float	mat4[16];
// typedef GLfloat	vec4[4];
// typedef GLfloat	vec3[3];

void	set_mat4_identity(mat4 mat);
void	print_mat4(mat4 mat);
void	rotate_mat4(mat4 mat, float x, float y, float z);
void	translate_mat4(mat4 mat, float x, float y, float z);
void	set_mat4_projection(mat4 mat, float fov, float near, float far,
	float aspect);

#endif
