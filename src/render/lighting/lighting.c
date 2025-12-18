/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:54:43 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting_int.h"
#include <math.h>
#include <stddef.h>

/*
** Casts a shadow ray from hit point toward light.
** Returns 1 if an object blocks the light path.
*/
int	is_in_shadow(t_scene *scene, t_vec3 hit_point, t_light *light)
{
	t_ray	shadow_ray;
	t_vec3	to_light;
	double	light_distance;
	t_hit	shadow_hit;

	to_light = vec3_sub(light->pos, hit_point);
	light_distance = sqrt(vec3_dot(to_light, to_light));
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(to_light, 0.001
				/ light_distance));
	shadow_ray.direction = vec3_normalize(to_light);
	shadow_hit = find_closest_hit(&shadow_ray, scene);
	if (shadow_hit.hit && shadow_hit.t < light_distance - 0.001)
		return (1);
	return (0);
}

t_color	calculate_ambient(t_ambient *ambient, t_color object_color)
{
	t_color	ambient_contribution;

	ambient_contribution = color_multiply(ambient->color, object_color);
	ambient_contribution = color_scale(ambient_contribution, ambient->ratio);
	return (ambient_contribution);
}

t_color	calc_diff(t_light *light, t_light_calc *params)
{
	t_vec3	light_dir;
	double	light_intensity;

	light_dir = vec3_sub(light->pos, params->hit_point);
	light_dir = vec3_normalize(light_dir);
	light_intensity = vec3_dot(params->normal, light_dir);
	if (light_intensity < 0)
		light_intensity = 0;
	light_intensity *= light->brightness;
	return (color_scale(color_multiply(light->color, params->color),
			light_intensity));
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit, t_vec3 cam_pos,
		void *mlx)
{
	t_color			final_color;
	t_color			object_color;
	t_vec3			bumped_normal;
	t_light_calc	calc;
	int				i;

	object_color = get_pattern_color(hit);
	bumped_normal = hit->normal;
	if (hit->object->bump.enabled && hit->object->bump.img)
		bumped_normal = apply_bump_map(mlx, hit);
	calc = (t_light_calc){hit->point, bumped_normal, cam_pos, object_color,
		hit->object->phong};
	final_color = calculate_ambient(&scene->ambient, object_color);
	i = -1;
	while (++i < scene->light_count)
	{
		if (!is_in_shadow(scene, hit->point, &scene->lights[i]))
		{
			final_color = color_add(final_color, calc_diff(&scene->lights[i],
						&calc));
			final_color = color_add(final_color,
					calc_specular(&scene->lights[i], &calc));
		}
	}
	return (color_clamp(final_color));
}
