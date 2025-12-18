/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:10:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:59 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_int.h"
#include <math.h>

static t_color	invert_color(t_color c)
{
	t_color	result;

	result.r = 255 - c.r;
	result.g = 255 - c.g;
	result.b = 255 - c.b;
	return (result);
}

static void	compute_plane_pattern_uv(t_hit *hit, double *u, double *v)
{
	*u = hit->point.x * hit->object->check.scale;
	*v = hit->point.z * hit->object->check.scale;
}

static void	compute_sphere_pattern_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local_point;
	double	theta;
	double	phi;

	local_point = vec3_sub(hit->point, hit->object->shape.sphere.center);
	local_point = vec3_normalize(local_point);
	theta = atan2(local_point.z, local_point.x);
	phi = acos(local_point.y);
	*u = (theta + M_PI) / (2 * M_PI) * hit->object->check.scale;
	*v = phi / M_PI * hit->object->check.scale;
}

static void	compute_cylinder_pattern_uv(t_hit *hit, double *u, double *v)
{
	t_vec3	local_point;
	t_vec3	radial;
	double	theta;
	double	height;
	double	radial_len;

	local_point = vec3_sub(hit->point, hit->object->shape.cylinder.center);
	height = vec3_dot(local_point, hit->object->shape.cylinder.axis);
	radial = vec3_sub(local_point, vec3_scale(hit->object->shape.cylinder.axis,
				height));
	radial_len = sqrt(vec3_dot(radial, radial));
	if (radial_len > 0.001)
	{
		radial = vec3_scale(radial, 1.0 / radial_len);
		theta = atan2(radial.z, radial.x);
		*u = (theta + M_PI) / (2 * M_PI) * hit->object->check.scale;
	}
	else
		*u = 0;
	*v = height * hit->object->check.scale;
}

t_color	get_pattern_color(t_hit *hit)
{
	double	uv[2];
	int		pattern[2];
	t_color	base_color;

	base_color = get_texture_color(hit);
	if (!hit->object->check.enabled)
		return (base_color);
	if (hit->object->type == OBJ_PLANE)
		compute_plane_pattern_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_SPHERE)
		compute_sphere_pattern_uv(hit, &uv[0], &uv[1]);
	else if (hit->object->type == OBJ_CYLINDER || hit->object->type == OBJ_CONE)
		compute_cylinder_pattern_uv(hit, &uv[0], &uv[1]);
	else
		return (base_color);
	pattern[0] = (int)floor(uv[0] + 0.000001);
	pattern[1] = (int)floor(uv[1] + 0.000001);
	if (((pattern[0] + pattern[1]) % 2) == 0)
		return (base_color);
	return (invert_color(base_color));
}
