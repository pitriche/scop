/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:12:27 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/07 15:13:21 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef float	mat4[16];
// typedef GLfloat	vec4[4];
// typedef GLfloat	vec3[3];

void	set_mat4_identity(mat4 mat);
void	print_mat4(mat4 mat);


#endif
