/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:23:57 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 03:29:25 by mgallo           ###   ########.fr       */
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
