/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:26:52 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/15 21:55:57 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

void			mouse_callback(GLFWwindow* w, double x, double y)
{
	t_env	*env;

	env = (t_env *)glfwGetWindowUserPointer(w);
	if (!env)
		return ;
	env->system.mouse.x = (float)x;
	env->system.mouse.y = (float)y;
}

void			key_callback(GLFWwindow *w, int k, int sc, int a, int m)
{
	t_env	*env;

	env = (t_env *)glfwGetWindowUserPointer(w);
	if (!env)
		return ;
	if (k == GLFW_KEY_M && a == GLFW_PRESS)
		env->system.mode = (env->system.mode + 1) % 3;
	printf("mode: %d\n", env->system.mode);
}
