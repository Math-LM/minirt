/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 13:44:12 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../closest_hit_int.h"
#include "vec3.h"
#include <math.h>

static int	check_cone_base(t_ray *ray, t_cone *cone, double *t)
{
	t_vec3	base_center;
	double	t_base;
	t_vec3	hit_point;
	t_vec3	to_hit;
	double	dist_sq;

	base_center = vec3_add(cone->center, vec3_scale(cone->axis, cone->height
				/ 2));
	if (intersect_plane(ray, &(t_plane){base_center, cone->axis}, &t_base))
	{
		hit_point = vec3_add(ray->origin, vec3_scale(ray->direction, t_base));
		to_hit = vec3_sub(hit_point, base_center);
		dist_sq = vec3_dot(to_hit, to_hit);
		if (dist_sq <= (cone->diameter / 2) * (cone->diameter / 2)
			&& t_base > 0.001 && t_base < *t)
		{
			*t = t_base;
			return (1);
		}
	}
	return (0);
}

static void	init_cone_vars(t_ray *ray, t_cone *cone, t_cyl_vars *v)
{
	t_vec3	apex;
	double	tan_sq;
	double	dv;
	double	co_v;

	apex = vec3_sub(cone->center, vec3_scale(cone->axis, cone->height / 2));
	v->oc = vec3_sub(ray->origin, apex);
	tan_sq = pow(cone->diameter / (2.0 * cone->height), 2);
	dv = vec3_dot(ray->direction, cone->axis);
	co_v = vec3_dot(v->oc, cone->axis);
	v->abc[0] = vec3_dot(ray->direction, ray->direction) - (1 + tan_sq) * dv
		* dv;
	v->abc[1] = 2.0 * (vec3_dot(ray->direction, v->oc) - (1 + tan_sq) * dv
			* co_v);
	v->abc[2] = vec3_dot(v->oc, v->oc) - (1 + tan_sq) * co_v * co_v;
}

static int	check_body_hit_cone(t_cone *cone, t_ray *ray, t_cyl_vars *v,
		double *t)
{
	t_vec3	hit;
	double	m;
	int		found;
	t_vec3	apex;

	apex = vec3_sub(cone->center, vec3_scale(cone->axis, cone->height / 2));
	found = 0;
	if (v->t_vals[0] > 0.001)
	{
		hit = vec3_add(ray->origin, vec3_scale(ray->direction, v->t_vals[0]));
		m = vec3_dot(vec3_sub(hit, apex), cone->axis);
		if (m >= 0 && m <= cone->height)
		{
			*t = v->t_vals[0];
			found = 1;
		}
	}
	if (v->t_vals[1] > 0.001 && (!found || v->t_vals[1] < *t))
	{
		hit = vec3_add(ray->origin, vec3_scale(ray->direction, v->t_vals[1]));
		m = vec3_dot(vec3_sub(hit, apex), cone->axis);
		if (m >= 0 && m <= cone->height)
			*t = v->t_vals[1];
	}
	return (*t < INFINITY);
}

int	intersect_cone(t_ray *ray, t_cone *cone, double *t)
{
	t_cyl_vars	v;

	*t = INFINITY;
	init_cone_vars(ray, cone, &v);
	v.disc = v.abc[1] * v.abc[1] - 4 * v.abc[0] * v.abc[2];
	if (v.disc < 0)
		return (check_cone_base(ray, cone, t));
	v.t_vals[0] = (-v.abc[1] - sqrt(v.disc)) / (2 * v.abc[0]);
	v.t_vals[1] = (-v.abc[1] + sqrt(v.disc)) / (2 * v.abc[0]);
	check_body_hit_cone(cone, ray, &v, t);
	check_cone_base(ray, cone, t);
	return (*t > 0.001 && *t != INFINITY);
}
