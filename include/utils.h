/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:37:52 by pitriche          #+#    #+#             */
/*   Updated: 2021/06/04 16:56:30 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stddef.h> /* size_t */

unsigned long	usec_timestamp(void);
void			ft_bzero(void *ptr, size_t size);
const char		*read_file(const char *filename);

#endif
