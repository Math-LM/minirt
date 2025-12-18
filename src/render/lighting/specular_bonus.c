/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:50:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 13:43:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting_int.h"
#include <math.h>

t_color	calc_specular(t_light *light, t_light_calc *calc)
{
	t_vec3	light_dir;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	spec;

	light_dir = vec3_normalize(vec3_sub(light->pos, calc->hit_point));
	view_dir = vec3_normalize(vec3_sub(calc->cam_pos, calc->hit_point));
	reflect_dir = vec3_sub(vec3_scale(calc->normal,
				2.0 * vec3_dot(calc->normal, light_dir)), light_dir);
	reflect_dir = vec3_normalize(reflect_dir);
	spec = vec3_dot(view_dir, reflect_dir);
	if (spec < 0)
		spec = 0;
	spec = pow(spec, calc->phong.shininess) * calc->phong.specular;
	return (color_scale(light->color, spec));
}
