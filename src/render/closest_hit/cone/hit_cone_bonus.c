/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:35:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:04 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../closest_hit_int.h"
#include "vec3.h"
#include <math.h>

static t_vec3	calculate_cone_normal(t_vec3 hit_point, t_cone *cone)
{
	t_vec3	apex;
	t_vec3	to_hit;
	double	m;
	double	tan_sq;
	t_vec3	normal;

	apex = vec3_sub(cone->center, vec3_scale(cone->axis, cone->height / 2));
	to_hit = vec3_sub(hit_point, apex);
	m = vec3_dot(to_hit, cone->axis);
	if (fabs(m - cone->height) < 0.001)
		return (cone->axis);
	tan_sq = pow(cone->diameter / (2.0 * cone->height), 2);
	normal = vec3_sub(to_hit, vec3_scale(cone->axis, m * (1.0 + tan_sq)));
	return (vec3_normalize(normal));
}

void	process_cone_hit(t_ray *ray, t_object *obj, double t, t_hit *closest)
{
	closest->hit = 1;
	closest->t = t;
	closest->object = obj;
	closest->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	closest->normal = calculate_cone_normal(closest->point, &obj->shape.cone);
}
