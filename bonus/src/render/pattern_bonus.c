/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:10:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 17:31:58 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "vec3_bonus.h"
#include <math.h>

static t_color	invert_color(t_color c)
{
	t_color	result;

	result.r = 255 - c.r;
	result.g = 255 - c.g;
	result.b = 255 - c.b;
	return (result);
}

t_color	get_pattern_color(t_hit *hit)
{
	double	u;
	double	v;
	int		pattern_u;
	int		pattern_v;
	t_vec3	local_point;
	double	theta;
	double	phi;

	if (hit->object->material.pattern == PATTERN_NONE)
		return (hit->object->material.color);
	if (hit->object->type == OBJ_PLANE)
	{
		u = hit->point.x * hit->object->material.pat_scale;
		v = hit->point.z * hit->object->material.pat_scale;
	}
	else if (hit->object->type == OBJ_SPHERE)
	{
		local_point = vec3_sub(hit->point, hit->object->shape.sphere.center);
		local_point = vec3_normalize(local_point);
		theta = atan2(local_point.z, local_point.x);
		phi = acos(local_point.y);
		u = theta / (2 * M_PI) * hit->object->material.pat_scale;
		v = phi / M_PI * hit->object->material.pat_scale;
	}
	else
		return (hit->object->material.color);
	pattern_u = (int)floor(u);
	pattern_v = (int)floor(v);
	if (((pattern_u + pattern_v) % hit->object->material.pat_type) == 0)
		return (hit->object->material.color);
	return (invert_color(hit->object->material.color));
}
