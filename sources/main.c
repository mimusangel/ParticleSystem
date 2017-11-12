/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:40:03 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 03:19:21 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

static int		loop_cl(t_env *env)
{
	env->cl.error = clSetKernelArg(env->cl.kernel, 0, sizeof(env->cl.in_buffer), &(env->cl.in_buffer));
	if ((env->cl.error = clEnqueueNDRangeKernel(env->cl.queue, env->cl.kernel, 1, 0, (size_t[1]){1}, NULL, 0, NULL, NULL)) != CL_SUCCESS)
		return (ft_puterror("OpenCL error: Enqueue Range Kernel"));
	clFinish(env->cl.queue);
	return (1);
}

static void		loop(t_env *env)
{
	env->run = 1;
	while (env->run)
	{
		if (glfwWindowShouldClose(env->win)
			|| glfwGetKey(env->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			env->run = 0;
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			loop_cl(env);

			glfwSwapBuffers(env->win);
			glfwPollEvents();
		}
	}
}

int				main(void)
{
	t_env	env;

	env.nb_particles = 1000;
	if (init(&env))
		loop(&env);
	terminate(&env);
	return (0);
}
