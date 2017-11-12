/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:40:03 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 07:16:14 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

static int		loop_cl(t_env *env)
{
	clEnqueueAcquireGLObjects(env->cl.queue, 1, &(env->cl.gl_buffer), 0, 0, 0);
	env->cl.error = clSetKernelArg(env->cl.kernel, 0, sizeof(env->cl.gl_buffer),
		&(env->cl.gl_buffer));
	if ((env->cl.error = clEnqueueNDRangeKernel(env->cl.queue, env->cl.kernel,
		1, 0, (size_t[1]){env->nb_particles}, NULL, 0, NULL, NULL))
		!= CL_SUCCESS)
		return (ft_puterror("OpenCL error: Enqueue Range Kernel"));
	clEnqueueReleaseGLObjects(env->cl.queue, 1, &(env->cl.gl_buffer), 0, 0, 0);
	clFinish(env->cl.queue);
	return (1);
}

static void		loop(t_env *env)
{
	env->run = 1;
	glfwSetTime(0.0);
	env->frame = 0;
	while (env->run)
	{
		glfwMakeContextCurrent(env->win);
		if (glfwWindowShouldClose(env->win)
			|| glfwGetKey(env->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			env->run = 0;
		else
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(env->program_shader);
			glPointSize(2.f);
			glBindVertexArray(env->vao);
			glDrawArrays(GL_POINTS, 0, env->nb_particles);
			glBindVertexArray(0);
			glPointSize(1.f);
			glfwSwapBuffers(env->win);
			glfwPollEvents();
			glFinish();
			loop_cl(env);
			env->frame += 1;
			if (glfwGetTime() >= 1.0)
			{
				printf("fps: %zu\n", env->frame);
				env->frame = 0;
				glfwSetTime(glfwGetTime() - 1);
			}
		}
	}
}

int				main(void)
{
	t_env	env;

	env.nb_particles = 500000;
	if (init(&env))
		loop(&env);
	terminate(&env);
	return (0);
}
