/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:23:09 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser_int.h"
#include "lft_conversion.h"
#include "lft_error.h"
#include "lft_string.h"

static int	find_color_index(char **params)
{
	int	color_idx;

	color_idx = 5;
	while (params[color_idx] && !ft_strchr(params[color_idx], ','))
		color_idx++;
	return (color_idx);
}

static int	validate_cone_params(char **params, t_object *obj, int color_idx)
{
	if (!parse_vec3(params[1], &obj->shape.cone.center)
		|| !parse_vec3(params[2], &obj->shape.cone.axis)
		|| !is_valid_normalized(obj->shape.cone.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cone.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cone.height)
		|| !parse_color(params[color_idx], &obj->color))
		return (0);
	return (1);
}

int	parse_cone(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;
	int			color_idx;

	if (scene->obj_count >= MAX_OBJECTS)
		return (put_error_msg("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 6)
	{
		free_split(params);
		return (put_error_msg("Invalid Cone param count"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_CONE;
	color_idx = find_color_index(params);
	if (!validate_cone_params(params, obj, color_idx))
	{
		free_split(params);
		return (put_error_msg("Invalid Cone param"));
	}
	obj->shape.cone.axis = vec3_normalize(obj->shape.cone.axis);
	init_phong(obj);
	parse_material_options(params, color_idx + 1, obj);
	scene->obj_count++;
	return (free_split(params), 0);
}
