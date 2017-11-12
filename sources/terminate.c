/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 00:27:27 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 06:25:07 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

static void				terminate_cl(t_cl *cl)
{
	if (cl->queue != NULL)
		cl->error = clReleaseCommandQueue(cl->queue);
	if (cl->context != NULL)
		cl->error = clReleaseContext(cl->context);
	if (cl->kernel != NULL)
		cl->error = clReleaseKernel(cl->kernel);
	if (cl->program != NULL)
		cl->error = clReleaseProgram(cl->program);
	if (cl->gl_buffer != NULL)
		cl->error = clReleaseMemObject(cl->gl_buffer);
}

void					terminate(t_env *env)
{
	terminate_cl(&(env->cl));
	if (env->win)
		glfwDestroyWindow(env->win);
	glfwTerminate();
}
