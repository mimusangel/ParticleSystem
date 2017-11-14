/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 23:39:22 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/14 00:26:51 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLE_H
# define PARTICLE_H

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <OpenCL/opencl.h>
# include <math.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE 8192
# endif
# ifndef PI
#  define PI 3.14159265359f
# endif

# ifndef TORADIANS
#  define TORADIANS(x)	(x * 0.0174533f)
# endif

typedef struct			s_xyzw
{
	float				x;
	float				y;
	float				z;
	float				w;
}						t_xyzw;

typedef struct			s_cl
{
	cl_platform_id		platform_id;
	cl_uint				platform_count;
	cl_device_id		device_id;
	cl_uint				device_count;
	cl_int				error;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				gl_pos;
	cl_mem				gl_vel;
}						t_cl;

typedef struct			s_env
{
	GLFWwindow			*win;
	t_cl				cl;
	int					run;
	int					nb_particles;
	GLuint				vao;
	GLuint				gl_pos_id;
	GLuint				gl_vel_id;
	GLuint				gl_color_id;
	GLuint				program_shader;
	GLfloat				*projection;
	GLfloat				*model;
	size_t				frame;
}						t_env;

/*
** main.c
*/

/*
** log.c
*/
size_t					ft_strlen(const char *str);
int						ft_putlog(const char *log, const char *error);
int						ft_puterror(const char *str);
void					opencl_error(const char *err, const void *p, size_t cb,
	void *u);
/*
** init.c
*/
int						init(t_env *env);
/*
** terminate.c
*/
void					terminate(t_env *env);
/*
** file.c
*/
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strchr(const char *str, const char c);
void					ft_strcpy(char *dest, char *src, size_t size);
char					*get_file_content(const char *path, size_t *size);
size_t					get_str_line(char *str, char **line);
/*
** shader.c
*/
GLuint					load_shaders(const GLchar *v_src, const GLchar *f_src);
/*
** uniform.c
*/
void					uniform_int(GLuint program, GLchar *name, GLint value);
void					uniform_float(GLuint program, GLchar *name,
	GLfloat value);
void					uniform_mat4(GLuint program, GLchar *name,
	GLfloat *mat);
/*
** mat4.c
*/
GLfloat					*mat4_create(void);
GLfloat					*mat4_identity(void);
GLfloat					*mat4_perspective(float fov, float asp, float near,
	float far);
GLfloat					*mat4_translate(float x, float y, float z);
GLfloat					*mat4_multiplie(float *m0, float *m1);
/*
** rotate.c
*/
GLfloat					*mat4_axisangle(GLfloat angle, GLfloat x, GLfloat y,
	GLfloat z);
GLfloat					*mat4_rotate(GLfloat x, GLfloat y, GLfloat z);
/*
** quat.c
*/
GLfloat					*quat_tomat4(t_xyzw *quat);
t_xyzw					*quat_mul(t_xyzw *q1, t_xyzw *q2);
t_xyzw					*quat_axisangle(GLfloat angle, GLfloat x, GLfloat y,
	GLfloat z);
#endif
