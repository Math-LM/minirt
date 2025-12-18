/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:00:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:22 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../closest_hit_int.h"
#include "vec3.h"
#include <math.h>

/*
** Ray-plane intersection using geometric formula.
** Returns 0 if ray is parallel to plane or intersection is behind ray origin.
*/
int	intersect_plane(t_ray *ray, t_plane *plane, double *t)
{
	double	denom;
	double	numer;
	t_vec3	p0_to_origin;

	denom = vec3_dot(plane->normal, ray->direction);
	if (fabs(denom) < 0.0001)
		return (0);
	p0_to_origin = vec3_sub(plane->point, ray->origin);
	numer = vec3_dot(p0_to_origin, plane->normal);
	*t = numer / denom;
	if (*t < 0.001)
		return (0);
	return (1);
}
