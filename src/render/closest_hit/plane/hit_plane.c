/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:05:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 13:44:23 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "../closest_hit_int.h"

void	process_plane_hit(t_ray *ray, t_object *obj, double t, t_hit *closest)
{
	closest->hit = 1;
	closest->t = t;
	closest->object = obj;
	closest->point = vec3_add(ray->origin, vec3_scale(ray->direction, t));
	closest->normal = obj->shape.plane.normal;
}
