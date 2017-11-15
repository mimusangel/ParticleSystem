/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:26:52 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/15 03:11:29 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

void			mouse_callback(GLFWwindow* w, double x, double y)
{
	t_env	*env;

	env = (t_env *)glfwGetWindowUserPointer(w);
	if (!env)
		return ;
	env->mouse.x = (float)x;
	env->mouse.y = (float)y;
}
