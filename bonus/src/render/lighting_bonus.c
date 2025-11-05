/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:54:43 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 17:27:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <math.h>

static int	is_in_shadow(t_scene *scene, t_vec3 hit_point, t_vec3 light_pos)
{
	t_ray	shadow_ray;
	t_vec3	to_light;
	double	light_distance;
	t_hit	shadow_hit;

	to_light = vec3_sub(light_pos, hit_point);
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

t_color	calculate_diffuse(t_light *light, t_vec3 hit_point, t_vec3 normal,
		t_color object_color)
{
	t_vec3	light_dir;
	double	light_intensity;
	t_color	diffuse_contribution;

	light_dir = vec3_sub(light->pos, hit_point);
	light_dir = vec3_normalize(light_dir);
	light_intensity = vec3_dot(normal, light_dir);
	if (light_intensity < 0)
		light_intensity = 0;
	light_intensity *= light->brightness;
	diffuse_contribution = color_multiply(light->color, object_color);
	diffuse_contribution = color_scale(diffuse_contribution, light_intensity);
	return (diffuse_contribution);
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit)
{
	t_color	final_color;
	t_color	ambient;
	t_color	diffuse;
	t_color	object_color;
	int		i;

	object_color = get_pattern_color(hit);
	ambient = calculate_ambient(&scene->ambient, object_color);
	final_color = ambient;
	i = 0;
	while (i < scene->light_count)
	{
		if (!is_in_shadow(scene, hit->point, scene->lights[i].pos))
		{
			diffuse = calculate_diffuse(&scene->lights[i], hit->point,
					hit->normal, object_color);
			final_color = color_add(final_color, diffuse);
		}
		i++;
	}
	final_color = color_clamp(final_color);
	return (final_color);
}
