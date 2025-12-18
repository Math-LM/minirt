/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:00:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 14:32:38 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "../closest_hit_int.h"
#include <math.h>

/*
** Ray-sphere intersection using quadratic formula.
** Solves: ||ray.origin + t*ray.direction - sphere.center||^2 = radius^2
** Returns 1 if hit (and sets t to closest positive intersection), 0 otherwise.
*/
int	intersect_sphere(t_ray *ray, t_sphere *sphere, double *t)
{
	t_vec3	oc;
	double	abc[3];
	double	discriminant;
	double	t_vals[2];
	double	radius;

	radius = sphere->diameter / 2.0;
	oc = vec3_sub(ray->origin, sphere->center);
	abc[0] = vec3_dot(ray->direction, ray->direction);
	abc[1] = 2.0 * vec3_dot(oc, ray->direction);
	abc[2] = vec3_dot(oc, oc) - radius * radius;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (0);
	t_vals[0] = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	t_vals[1] = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (t_vals[0] > 0.001)
		*t = t_vals[0];
	else if (t_vals[1] > 0.001)
		*t = t_vals[1];
	else
		return (0);
	return (1);
}
