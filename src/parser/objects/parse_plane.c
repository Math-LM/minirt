/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 10:20:09 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 14:30:59 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft_conversion.h"
#include "lft_error.h"
#include "lft_string.h"
#include "../parser_int.h"

static int	validate_plane_params(char **params, t_object *obj)
{
	if (!parse_vec3(params[1], &obj->shape.plane.point)
		|| !parse_vec3(params[2], &obj->shape.plane.normal)
		|| !is_valid_normalized(obj->shape.plane.normal)
		|| !parse_color(params[3], &obj->color))
		return (0);
	return (1);
}

int	parse_plane(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (scene->obj_count >= MAX_OBJECTS)
		return (put_error_msg("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 4)
	{
		free_split(params);
		return (put_error_msg("Invalid Plane params count"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_PLANE;
	if (!validate_plane_params(params, obj))
	{
		free_split(params);
		return (put_error_msg("Invalid Plane param"));
	}
	obj->shape.plane.normal = vec3_normalize(obj->shape.plane.normal);
	init_phong(obj);
	parse_material_options(params, 4, obj);
	scene->obj_count++;
	free_split(params);
	return (0);
}
