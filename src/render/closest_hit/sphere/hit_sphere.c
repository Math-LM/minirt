/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:05:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 14:32:42 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "../closest_hit_int.h"

/*
** Records sphere hit information.
** Normal points outward from sphere center.
*/
void	process_sphere_hit(t_ray *ray, t_object *obj, double t, t_hit *closest)
{
	closest->hit = 1;
	closest->t = t;
	closest->object = obj;
	closest->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	closest->normal = vec3_sub(closest->point, obj->shape.sphere.center);
	closest->normal = vec3_normalize(closest->normal);
}
