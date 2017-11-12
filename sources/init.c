/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 00:13:25 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 03:25:24 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

static int				init_gl(t_env *env)
{
	if (!glfwInit())
		return (ft_puterror("Erreur init glfw!"));
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!(env->win = glfwCreateWindow(1280, 720, "ParticleSystem", NULL, NULL)))
		return (ft_puterror("Erreur creation de la fenetre!"));
	glfwMakeContextCurrent(env->win);
	glfwSetWindowUserPointer(env->win, env);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return (ft_puterror("Erreur init glew!"));
	return (1);
}

static int				init_cl(t_cl *cl)
{
	cl->platform_id = NULL;
	cl->error = clGetPlatformIDs(1, &(cl->platform_id), &(cl->platform_count));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: platform_id"));
	cl->device_id = NULL;
	cl->error = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
		&(cl->device_id), &(cl->device_count));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: device_id"));
	cl->context = NULL;
	cl->context = clCreateContext(NULL, 1, &(cl->device_id), opencl_error, NULL, &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: context"));
	cl->queue = NULL;
	cl->queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: queue"));
	return (1);
}

static int				init_program(t_env *env, t_cl *cl)
{
	char	*file_content;
	size_t	size;

	if (!(file_content = get_file_content("particles.cl", &size)))
		return (ft_puterror("Error: File doesn't exist or is empty!"));
	cl->program = clCreateProgramWithSource(cl->context, 1, (const char **)&file_content, (const size_t *)&size, &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: program source"));
	if ((cl->error = clBuildProgram(cl->program, 1, &(cl->device_id), NULL, NULL, NULL)) != CL_SUCCESS)
		return (ft_puterror("OpenCL error: build program"));
	cl->in_buffer = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int), &(env->nb_particles), &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: Create Buffer"));
	cl->kernel = clCreateKernel(cl->program , "particles", &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: kernel"));
	return (1);
}

static void				init_zero(t_env *env)
{
	env->win = NULL;
	env->cl.context = NULL;
	env->cl.queue = NULL;
	env->cl.program = NULL;
	env->cl.kernel = NULL;
	env->cl.in_buffer = NULL;
}

int						init(t_env *env)
{
	init_zero(env);
	if (!init_gl(env))
		return (0);
	if (!init_cl(&(env->cl)))
		return (0);
	if (!init_program(env, &(env->cl)))
		return (0);
	return (1);
}
