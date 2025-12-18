/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:05:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:36 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "closest_hit_int.h"
#include <math.h>

static void	check_sphere(t_ray *ray, t_object *obj, t_hit *closest)
{
	double	t;

	t = INFINITY;
	if (intersect_sphere(ray, &obj->shape.sphere, &t))
	{
		if (t < closest->t)
			process_sphere_hit(ray, obj, t, closest);
	}
}

static void	check_plane(t_ray *ray, t_object *obj, t_hit *closest)
{
	double	t;

	t = INFINITY;
	if (intersect_plane(ray, &obj->shape.plane, &t))
	{
		if (t < closest->t)
			process_plane_hit(ray, obj, t, closest);
	}
}

static void	check_cylinder(t_ray *ray, t_object *obj, t_hit *closest)
{
	double	t;

	t = INFINITY;
	if (intersect_cylinder(ray, &obj->shape.cylinder, &t))
	{
		if (t < closest->t)
			process_cylinder_hit(ray, obj, t, closest);
	}
}

static void	check_cone(t_ray *ray, t_object *obj, t_hit *closest)
{
	double	t;

	t = INFINITY;
	if (intersect_cone(ray, &obj->shape.cone, &t))
	{
		if (t < closest->t)
			process_cone_hit(ray, obj, t, closest);
	}
}

t_hit	find_closest_hit(t_ray *ray, t_scene *scene)
{
	t_hit	closest;
	int		i;

	closest.hit = 0;
	closest.t = INFINITY;
	i = 0;
	while (i < scene->obj_count)
	{
		if (scene->objects[i].type == OBJ_SPHERE)
			check_sphere(ray, &scene->objects[i], &closest);
		else if (scene->objects[i].type == OBJ_PLANE)
			check_plane(ray, &scene->objects[i], &closest);
		else if (scene->objects[i].type == OBJ_CYLINDER)
			check_cylinder(ray, &scene->objects[i], &closest);
		else if (scene->objects[i].type == OBJ_CONE)
			check_cone(ray, &scene->objects[i], &closest);
		i++;
	}
	return (closest);
}
