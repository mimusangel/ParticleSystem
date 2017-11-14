/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgallo <mgallo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:05:46 by mgallo            #+#    #+#             */
/*   Updated: 2017/11/14 00:26:31 by mgallo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle.h"

GLfloat			*quat_tomat4(t_xyzw *quat)
{
	GLfloat	*mat;
	GLfloat	tmp[9];

	if (!(mat = mat4_identity()))
		return (NULL);
	tmp[0] = quat->x * quat->x;
	tmp[1] = quat->x * quat->y;
	tmp[2] = quat->x * quat->z;
	tmp[3] = quat->x * quat->w;
	tmp[4] = quat->y * quat->y;
	tmp[5] = quat->y * quat->z;
	tmp[6] = quat->y * quat->w;
	tmp[7] = quat->z * quat->z;
	tmp[8] = quat->z * quat->w;
	mat[0] = 1.f - 2.f * (tmp[4] + tmp[7]);
	mat[1] = 2.f * (tmp[1] - tmp[8]);
	mat[2] = 2.f * (tmp[2] + tmp[6]);
	mat[4] = 2.f * (tmp[1] + tmp[8]);
	mat[5] = 1.f - 2.f * (tmp[0] + tmp[7]);
	mat[6] = 2.f * (tmp[5] - tmp[3]);
	mat[8] = 2.f * (tmp[2] - tmp[6]);
	mat[9] = 2.f * (tmp[5] + tmp[3]);
	mat[10] = 1.f - 2.f * (tmp[0] + tmp[4]);
	return (mat);
}

t_xyzw			*quat_mul(t_xyzw *q1, t_xyzw *q2)
{
	t_xyzw *quat;

	if (!(quat = (t_xyzw *)malloc(sizeof(t_xyzw))))
		return (NULL);
	quat->x = q1->x * q2->w + q1->y * q2->z - q1->z * q2->y + q1->w * q2->x;
    quat->y = -q1->x * q2->z + q1->y * q2->w + q1->z * q2->x + q1->w * q2->y;
    quat->z = q1->x * q2->y - q1->y * q2->x + q1->z * q2->w + q1->w * q2->z;
    quat->w = -q1->x * q2->x - q1->y * q2->y - q1->z * q2->z + q1->w * q2->w;
	return (quat);
}

t_xyzw			*quat_axisangle(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	t_xyzw	*quat;
	GLfloat	s;
	if (!(quat = (t_xyzw *)malloc(sizeof(t_xyzw))))
		return (NULL);
	s = (GLfloat)sinf(TORADIANS(angle));
	quat->x = x * s;
    quat->y = y * s;
    quat->z = z * s;
    quat->w = (GLfloat)cosf(TORADIANS(angle));
	return (quat);
}
