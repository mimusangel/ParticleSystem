/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 05:34:34 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/12 03:31:40 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

GLfloat		*mat4_axisangle(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat		*m;
	GLfloat		cs[2];
	GLfloat		tmp[3];

	if (!(m = mat4_identity()))
		return (NULL);
	cs[0] = (GLfloat)cosf(TORADIANS(angle));
	cs[1] = (GLfloat)sinf(TORADIANS(angle));
	tmp[2] = 1.0f - cs[0];
	m[0] = cs[0] + x * x * tmp[2];
	m[5] = cs[0] + y * y * tmp[2];
	m[10] = cs[0] + z * z * tmp[2];
	tmp[0] = x * y * tmp[2];
	tmp[1] = z * cs[1];
	m[1] = tmp[0] - tmp[1];
	m[4] = tmp[0] + tmp[1];
	tmp[0] = x * z * tmp[2];
	tmp[1] = y * cs[1];
	m[2] = tmp[0] + tmp[1];
	m[8] = tmp[0] - tmp[1];
	tmp[0] = y * z * tmp[2];
	tmp[1] = x * cs[1];
	m[6] = tmp[0] - tmp[1];
	m[9] = tmp[0] + tmp[1];
	return (m);
}

GLfloat		*mat4_rotate(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat	*rx;
	GLfloat	*ry;
	GLfloat	*rz;
	GLfloat	*tmp;
	GLfloat	*res;

	rx = mat4_axisangle(x, 1.f, 0.f, 0.f);
	ry = mat4_axisangle(y, 0.f, 1.f, 0.f);
	rz = mat4_axisangle(z, 0.f, 0.f, 1.f);
	tmp = mat4_multiplie(rz, ry);
	res = mat4_multiplie(tmp, rx);
	free(tmp);
	free(rz);
	free(ry);
	free(rx);
	return (res);
}
