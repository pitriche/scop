/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre42 <pierre42@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:37:52 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/09 15:47:10 by pierre42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stddef.h> /* size_t */

unsigned long	usec_timestamp(void);
void			ft_bzero(void *ptr, size_t size);
char			*read_file(const char *filename);
float			*load_bmp(const char *filename);

#endif
