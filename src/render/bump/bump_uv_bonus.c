/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_uv_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:40:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:23:58 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bump_int_bonus.h"
#include <math.h>

void	get_sphere_bump_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local;
	double	theta;
	double	phi;

	local = vec3_sub(hit->point, hit->object->shape.sphere.center);
	local = vec3_normalize(local);
	theta = atan2(local.z, local.x);
	phi = acos(local.y);
	*u = theta / (2.0 * M_PI);
	*v = phi / M_PI;
	if (*u < 0)
		*u += 1.0;
}

void	get_plane_bump_uv(t_hit *hit, double *u, double *v)
{
	*u = hit->point.x;
	*v = hit->point.z;
}

void	get_cylinder_bump_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local;
	t_vec3	axis;
	double	theta;
	double	projection;

	axis = hit->object->shape.cylinder.axis;
	local = vec3_sub(hit->point, hit->object->shape.cylinder.center);
	projection = vec3_dot(local, axis);
	*v = (projection / hit->object->shape.cylinder.height) + 0.5;
	local = vec3_sub(local, vec3_scale(axis, projection));
	local = vec3_normalize(local);
	theta = atan2(local.z, local.x);
	*u = theta / (2.0 * M_PI);
	if (*u < 0)
		*u += 1.0;
}

void	get_cone_bump_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local;
	t_vec3	axis;
	double	theta;
	double	projection;

	axis = hit->object->shape.cone.axis;
	local = vec3_sub(hit->point, hit->object->shape.cone.center);
	projection = vec3_dot(local, axis);
	*v = (projection / hit->object->shape.cone.height) + 0.5;
	local = vec3_sub(local, vec3_scale(axis, projection));
	local = vec3_normalize(local);
	theta = atan2(local.z, local.x);
	*u = theta / (2.0 * M_PI);
	if (*u < 0)
		*u += 1.0;
}
