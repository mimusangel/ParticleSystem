/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:40:03 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/15 23:12:58 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

static int		loop_cl(t_env *env)
{
	clEnqueueAcquireGLObjects(env->cl.queue, 1, &(env->cl.gl_pos), 0, 0, 0);
	clEnqueueAcquireGLObjects(env->cl.queue, 1, &(env->cl.gl_vel), 0, 0, 0);
	env->cl.error = clSetKernelArg(env->cl.kernel, 0, sizeof(env->cl.gl_pos),
		&(env->cl.gl_pos));
	env->cl.error = clSetKernelArg(env->cl.kernel, 1, sizeof(env->cl.gl_vel),
		&(env->cl.gl_vel));
	env->cl.error = clSetKernelArg(env->cl.kernel, 2, sizeof(env->cl.system),
		&(env->cl.system));
	env->cl.error = clEnqueueWriteBuffer(env->cl.queue, env->cl.system,
		CL_TRUE, 0, sizeof(t_system), &(env->system), 0, NULL, NULL);
	if ((env->cl.error = clEnqueueNDRangeKernel(env->cl.queue, env->cl.kernel,
		1, 0, (size_t[1]){env->nb_particles}, NULL, 0, NULL, NULL))
		!= CL_SUCCESS)
		return (ft_puterror("OpenCL error: Enqueue Range Kernel"));
	clEnqueueReleaseGLObjects(env->cl.queue, 1, &(env->cl.gl_vel), 0, 0, 0);
	clEnqueueReleaseGLObjects(env->cl.queue, 1, &(env->cl.gl_pos), 0, 0, 0);
	clFinish(env->cl.queue);
	return (1);
}

static void		loop_shader(t_env *env)
{
	static t_xyzw	rot = (t_xyzw){0.0, 0.0, 0.0, 0.0};
	GLfloat		*tmp[2];

	glUseProgram(env->program_shader);
	uniform_xyzw(env->program_shader, "gravity", &(env->system.gravity));
	// uniform_mat4(env->program_shader, "projection", env->projection);
	// if (env->model)
	// 	free(env->model);
	// tmp[0] = mat4_translate(0, 0, 4);
	// tmp[1] = mat4_rotate(rot.x, rot.y, rot.z);
	// env->model = mat4_multiplie(tmp[0], tmp[1]);
	// free(tmp[0]);
	// free(tmp[1]);
	// uniform_mat4(env->program_shader, "model", env->model);
	// uniform_mat4(env->program_shader, "view", env->model);
	glBindVertexArray(env->vao);
	glDrawArrays(GL_POINTS, 0, env->nb_particles);
	glBindVertexArray(0);
	rot.x += 0.05f;
	rot.y += 0.1f;
	rot.z -= 0.025f;
}

static void		loop_input(t_env *env)
{
	int width;
	int height;

	if (glfwGetMouseButton(env->win, GLFW_MOUSE_BUTTON_LEFT)== GLFW_PRESS)
	{
		glfwGetWindowSize(env->win, &width, &height);
		env->system.gravity.x = (env->system.mouse.x / (float)width) * 2.0f - 1.0f;
		env->system.gravity.y = -((env->system.mouse.y / (float)height) * 2.0f - 1.0f);
	}
}

static void		loop(t_env *env)
{
	env->run = 1;
	glfwSetTime(0.0);
	glEnable(GL_DEPTH_TEST);
	while (env->run)
	{
		glfwMakeContextCurrent(env->win);
		if (glfwWindowShouldClose(env->win)
			|| glfwGetKey(env->win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			env->run = 0;
		else
		{
			loop_input(env);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			loop_shader(env);
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

	env.frame = 0;
	env.nb_particles = 3000000;
	env.system.mode = 0;
	if (init(&env))
		loop(&env);
	terminate(&env);
	return (0);
}
