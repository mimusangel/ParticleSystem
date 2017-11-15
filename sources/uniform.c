/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:23:57 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/15 03:17:50 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

void		uniform_mat4(GLuint program, GLchar *name, GLfloat *mat)
{
	GLint id;

	id = glGetUniformLocation(program, name);
	glUniformMatrix4fv(id, 1, GL_FALSE, mat);
}

void		uniform_float(GLuint program, GLchar *name, GLfloat value)
{
	GLint id;

	id = glGetUniformLocation(program, name);
	glUniform1f(id, value);
}

void		uniform_int(GLuint program, GLchar *name, GLint value)
{
	GLint id;

	id = glGetUniformLocation(program, name);
	glUniform1i(id, value);
}

void		uniform_xyzw(GLuint program, GLchar *name, t_xyzw *value)
{
	GLint id;

	id = glGetUniformLocation(program, name);
	glUniform4f(id, value->x, value->y, value->z, value->w);
}
