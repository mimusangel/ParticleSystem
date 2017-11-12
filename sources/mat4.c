/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:13:37 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 03:31:02 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

GLfloat		*mat4_create(void)
{
	size_t	i;
	GLfloat	*mat;

	if (!(mat = (GLfloat *)malloc(sizeof(GLfloat) * 16)))
		return (NULL);
	i = 0;
	while (i < 16)
	{
		mat[i] = 0.f;
		i++;
	}
	return (mat);
}

GLfloat		*mat4_identity(void)
{
	GLfloat	*mat;

	if (!(mat = mat4_create()))
		return (NULL);
	mat[0] = 1.f;
	mat[5] = 1.f;
	mat[10] = 1.f;
	mat[15] = 1.f;
	return (mat);
}

GLfloat		*mat4_perspective(float fov, float asp, float near, float far)
{
	GLfloat	*mat;
	GLfloat	t;

	if (!(mat = mat4_create()))
		return (NULL);
	t = 1.0f / tanf(TORADIANS(fov / 2.0f));
	mat[0] = t / asp;
	mat[5] = t;
	mat[10] = (-near - far) / (near - far);
	mat[11] = 1.0f;
	mat[14] = 2.0f * far * near / (near - far);
	return (mat);
}

GLfloat		*mat4_translate(float x, float y, float z)
{
	GLfloat		*m;

	if (!(m = mat4_identity()))
		return (NULL);
	m[12] = x;
	m[13] = y;
	m[14] = z;
	return (m);
}

GLfloat		*mat4_multiplie(float *m0, float *m1)
{
	GLfloat	*m;
	int		x;
	int		y;

	if (!(m = mat4_create()))
		return (NULL);
	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
		{
			m[x + y * 4] = m1[0 + y * 4] * m0[x + 0 * 4]
				+ m1[1 + y * 4] * m0[x + 1 * 4] + m1[2 + y * 4] * m0[x + 2 * 4]
				+ m1[3 + y * 4] * m0[x + 3 * 4];
		}
	}
	return (m);
}
