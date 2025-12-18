/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:00:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 13:48:40 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "../closest_hit_int.h"
#include <math.h>

/*
** Checks if ray intersects a cylinder cap (circular disk at end).
** Cap is treated as a plane with radius check.
*/
static int	check_cap(t_ray *ray, t_vec3 cap_center, t_cylinder *cyl, double *t)
{
	double	t_cap;
	t_vec3	hit_point;
	t_vec3	to_hit;
	double	dist_sq;

	if (intersect_plane(ray, &(t_plane){cap_center, cyl->axis}, &t_cap))
	{
		hit_point = vec3_add(ray->origin, vec3_scale(ray->direction, t_cap));
		to_hit = vec3_sub(hit_point, cap_center);
		dist_sq = vec3_dot(to_hit, to_hit);
		if (dist_sq <= (cyl->diameter / 2) * (cyl->diameter / 2) && t_cap < *t)
		{
			*t = t_cap;
			return (1);
		}
	}
	return (0);
}

/*
** Tests intersection with both cylinder caps (top and bottom).
*/
static int	check_cylinder_caps(t_ray *ray, t_cylinder *cyl, double *t)
{
	t_vec3	cap_center;
	int		hit;

	hit = 0;
	cap_center = vec3_add(cyl->center, vec3_scale(cyl->axis, cyl->height / 2));
	hit |= check_cap(ray, cap_center, cyl, t);
	cap_center = vec3_sub(cyl->center, vec3_scale(cyl->axis, cyl->height / 2));
	hit |= check_cap(ray, cap_center, cyl, t);
	return (hit || (*t != INFINITY));
}

/*
** Initializes variables for cylinder body intersection.
** Projects ray and origin onto plane perpendicular to cylinder axis.
*/
static void	init_cylinder_vars(t_ray *ray, t_cylinder *cyl, t_cyl_vars *v)
{
	v->oc = vec3_sub(ray->origin, cyl->center);
	v->d_proj = vec3_sub(ray->direction, vec3_scale(cyl->axis,
				vec3_dot(ray->direction, cyl->axis)));
	v->oc_proj = vec3_sub(v->oc, vec3_scale(cyl->axis, vec3_dot(v->oc,
					cyl->axis)));
	v->abc[0] = vec3_dot(v->d_proj, v->d_proj);
	v->abc[1] = 2.0 * vec3_dot(v->d_proj, v->oc_proj);
	v->abc[2] = vec3_dot(v->oc_proj, v->oc_proj) - pow(cyl->diameter / 2, 2);
	v->disc = v->abc[1] * v->abc[1] - 4 * v->abc[0] * v->abc[2];
}

/*
** Validates that body intersection points are within cylinder height bounds.
** Parameter m is the signed distance along cylinder axis from center.
*/
static int	check_body_hit(t_ray *ray, t_cylinder *cyl, t_cyl_vars *v,
		double *t)
{
	t_vec3	hit;
	double	m;

	if (v->t_vals[0] > 0.001)
	{
		hit = vec3_add(ray->origin, vec3_scale(ray->direction, v->t_vals[0]));
		m = vec3_dot(vec3_sub(hit, cyl->center), cyl->axis);
		if (fabs(m) <= cyl->height / 2)
			*t = v->t_vals[0];
	}
	if (v->t_vals[1] > 0.001 && v->t_vals[1] < *t)
	{
		hit = vec3_add(ray->origin, vec3_scale(ray->direction, v->t_vals[1]));
		m = vec3_dot(vec3_sub(hit, cyl->center), cyl->axis);
		if (fabs(m) <= cyl->height / 2)
			*t = v->t_vals[1];
	}
	return (*t != INFINITY);
}

/*
** Ray-cylinder intersection.
** Solves quadratic for infinite cylinder body, then checks height and caps.
*/
int	intersect_cylinder(t_ray *ray, t_cylinder *cyl, double *t)
{
	t_cyl_vars	v;

	init_cylinder_vars(ray, cyl, &v);
	*t = INFINITY;
	if (v.disc < 0)
		return (check_cylinder_caps(ray, cyl, t));
	v.t_vals[0] = (-v.abc[1] - sqrt(v.disc)) / (2 * v.abc[0]);
	v.t_vals[1] = (-v.abc[1] + sqrt(v.disc)) / (2 * v.abc[0]);
	check_body_hit(ray, cyl, &v, t);
	check_cylinder_caps(ray, cyl, t);
	return (*t > 0.001 && *t != INFINITY);
}
