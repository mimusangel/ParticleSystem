/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 00:16:47 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 02:43:01 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

size_t					ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int						ft_putlog(const char *str, const char *error)
{
	write(1, str, ft_strlen(str));
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return (0);
}

int						ft_puterror(const char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (0);
}

void					opencl_error(const char *err, const void *p, size_t cb,
	void *u)
{
	(void)p;
	(void)cb;
	(void)u;
	write(1, "Erreur OpenCL: ", 15);
	write(1, err, ft_strlen(err));
}
