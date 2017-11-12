/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 00:13:25 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 06:44:22 by mgallo           ###   ########.fr       */
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
	CGLContextObj     CGLGetCurrentContext(void);
	CGLShareGroupObj  CGLGetShareGroup(CGLContextObj);

	CGLContextObj     kCGLContext     = CGLGetCurrentContext();
	CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);

	cl_context_properties properties[] =
	{
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties) kCGLShareGroup,
		0
	};
	cl->platform_id = NULL;
	cl->error = clGetPlatformIDs(1, &(cl->platform_id), &(cl->platform_count));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: platform_id"));
	cl->device_id = NULL;
	if (clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
		&(cl->device_id), &(cl->device_count)) != CL_SUCCESS)
		return (ft_puterror("OpenCL error: device_id"));
	cl->context = NULL;
	cl->context = clCreateContext(properties, 1, &(cl->device_id), opencl_error,
		NULL, &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: context"));
	cl->queue = NULL;
	cl->queue = clCreateCommandQueue(cl->context, cl->device_id, 0,
		&(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: queue"));
	return (1);
}

static void				bind_cgl(t_env *env, t_cl *cl)
{
	glGenVertexArrays(1, &(env->vao));
	glBindVertexArray(env->vao);
	glGenBuffers(1, &(env->gl_buffer_id));
	glBindBuffer(GL_ARRAY_BUFFER, env->gl_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * env->nb_particles,
		NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	cl->gl_buffer = clCreateFromGLBuffer(cl->context, CL_MEM_READ_WRITE,
		env->gl_buffer_id, &(cl->error));
	glBindBuffer(GL_ARRAY_BUFFER, env->gl_buffer_id);
	t_xyzw *points = (t_xyzw *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for(int i = 0; i < env->nb_particles; i++)
	{
		points[i].x = ((float)rand() / (float)(RAND_MAX)) * 2.0f - 1.0f;
		points[i].y = ((float)rand() / (float)(RAND_MAX)) * 2.0f - 1.0f;
		points[i].z = 0.f;
		points[i].w = 1.f;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
}

static int				init_program(t_env *env, t_cl *cl)
{
	char	*file_content;
	size_t	size;

	if (!(file_content = get_file_content("particles.cl", &size)))
		return (ft_puterror("Error: File doesn't exist or is empty!"));
	cl->program = clCreateProgramWithSource(cl->context, 1,
		(const char **)&file_content, (const size_t *)&size, &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: program source"));
	if ((cl->error = clBuildProgram(cl->program, 1, &(cl->device_id), NULL,
		NULL, NULL)) != CL_SUCCESS)
		return (ft_puterror("OpenCL error: build program"));
	bind_cgl(env, cl);
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: bind Buffer GL"));
	cl->kernel = clCreateKernel(cl->program, "particles", &(cl->error));
	if (cl->error != CL_SUCCESS)
		return (ft_puterror("OpenCL error: kernel"));
	return (1);
}

int						init(t_env *env)
{
	size_t	size;

	env->win = NULL;
	env->cl.context = NULL;
	env->cl.queue = NULL;
	env->cl.program = NULL;
	env->cl.kernel = NULL;
	env->cl.gl_buffer = NULL;
	env->gl_buffer_id = 0;
	if (!init_gl(env))
		return (0);
	if (!init_cl(&(env->cl)))
		return (0);
	if (!init_program(env, &(env->cl)))
		return (0);
	env->program_shader = load_shaders(get_file_content("sample.vert", &size),
		get_file_content("sample.frag", &size));
	return (1);
}
