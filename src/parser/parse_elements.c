/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:15:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:23:26 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft_conversion.h"
#include "lft_error.h"
#include "lft_memory.h"
#include "lft_string.h"
#include "parser_int.h"
#include <limits.h>

int	parse_ambient(char *line, t_scene *scene)
{
	char	**params;

	if (scene->ambient.set)
		return (put_error_msg("Ambient lighting already defined"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) != 3)
	{
		free_split(params);
		return (put_error_msg("Invalid Ambient params count"));
	}
	if (!ft_stod_valid(params[1], &scene->ambient.ratio)
		|| !is_valid_range(scene->ambient.ratio, 0.0, 1.0))
	{
		free_split(params);
		return (put_error_msg("Invalid Ambient ratio"));
	}
	if (!parse_color(params[2], &scene->ambient.color))
	{
		free_split(params);
		return (put_error_msg("Invalid ambient color"));
	}
	scene->ambient.set = 1;
	free_split(params);
	return (0);
}

int	parse_camera(char *line, t_scene *scene)
{
	char	**params;

	if (scene->camera.set)
		return (put_error_msg("Camera already defined"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) != 4)
	{
		free_split(params);
		return (put_error_msg("Invalid Camera params count"));
	}
	if (!parse_vec3(params[1], &scene->camera.pos) || !parse_vec3(params[2],
			&scene->camera.orient) || !is_valid_normalized(scene->camera.orient)
		|| !ft_atoi_valid(params[3], &scene->camera.fov)
		|| !is_valid_range(scene->camera.fov, 0, 180))
	{
		free_split(params);
		return (put_error_msg("Invalid Camera params"));
	}
	scene->camera.orient = vec3_normalize(scene->camera.orient);
	scene->camera.set = 1;
	free_split(params);
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	char	**params;
	t_light	*light;

	if (scene->light_count >= MAX_LIGHTS)
		return (put_error_msg("Too many lights"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) != 4)
	{
		free_split(params);
		return (put_error_msg("Invalid Lights param count"));
	}
	light = &scene->lights[scene->light_count];
	if (!parse_vec3(params[1], &light->pos) || !ft_stod_valid(params[2],
			&light->brightness) || !is_valid_range(light->brightness, 0.0, 1.0)
		|| !parse_color(params[3], &light->color))
	{
		free_split(params);
		return (put_error_msg("Invalid Lights param"));
	}
	scene->light_count++;
	free_split(params);
	return (0);
}
