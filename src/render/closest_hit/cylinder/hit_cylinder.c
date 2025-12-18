/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:05:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:10 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../closest_hit_int.h"
#include "vec3.h"
#include <math.h>

/*
** Determines if hit point is on cylinder cap or body surface.
** For caps: normal is cylinder axis direction.
** For body: normal is perpendicular to axis, pointing outward.
*/
static void	calculate_cylinder_normal(t_object *obj, t_hit *closest)
{
	t_vec3	to_center;
	double	m;
	t_vec3	cap_center;

	to_center = vec3_sub(closest->point, obj->shape.cylinder.center);
	m = vec3_dot(to_center, obj->shape.cylinder.axis);
	if (fabs(m) >= obj->shape.cylinder.height / 2 - 0.001)
	{
		closest->normal = obj->shape.cylinder.axis;
		if (m < 0)
			closest->normal = vec3_negate(closest->normal);
	}
	else
	{
		cap_center = vec3_scale(obj->shape.cylinder.axis, m);
		closest->normal = vec3_sub(to_center, cap_center);
		closest->normal = vec3_normalize(closest->normal);
	}
}

void	process_cylinder_hit(t_ray *ray, t_object *obj, double t,
		t_hit *closest)
{
	closest->hit = 1;
	closest->t = t;
	closest->object = obj;
	closest->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	calculate_cylinder_normal(obj, closest);
}
