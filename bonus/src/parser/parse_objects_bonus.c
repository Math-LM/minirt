/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:20:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 17:29:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int_bonus.h"
#include "libft.h"

static void	init_material(t_material *mat, t_color color)
{
	mat->color = color;
	mat->specular = 0.5;
	mat->shininess = 32.0;
	mat->pattern = PATTERN_NONE;
	mat->pat_scale = 1.0;
	mat->pat_type = 1;
}

int	parse_sphere(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 4)
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_SPHERE;
	if (!parse_vec3(params[1], &obj->shape.sphere.center)
		|| !ft_stod_valid(params[2], &obj->shape.sphere.diameter)
		|| !parse_color(params[3], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, 4, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}

int	parse_plane(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 4)
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_PLANE;
	if (!parse_vec3(params[1], &obj->shape.plane.point)
		|| !parse_vec3(params[2], &obj->shape.plane.normal)
		|| !is_valid_normalized(obj->shape.plane.normal)
		|| !parse_color(params[3], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, 4, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 6)
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_CYLINDER;
	if (!parse_vec3(params[1], &obj->shape.cylinder.center)
		|| !parse_vec3(params[2], &obj->shape.cylinder.axis)
		|| !is_valid_normalized(obj->shape.cylinder.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cylinder.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cylinder.height)
		|| !parse_color(params[5], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, 6, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}

int	parse_cone(char *line, t_scene *scene)
{
	char		**params;
	t_object	*obj;
	int			color_idx;

	if (scene->obj_count >= MAX_OBJECTS)
		return (ft_puterr("Too many objects"));
	params = ft_split(line, " \t\n\r");
	if (count_split(params) < 6)
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	obj = &scene->objects[scene->obj_count];
	obj->type = OBJ_CONE;
	color_idx = 5;
	while (params[color_idx] && !ft_strchr(params[color_idx], ','))
		color_idx++;
	if (!parse_vec3(params[1], &obj->shape.cone.center)
		|| !parse_vec3(params[2], &obj->shape.cone.axis)
		|| !is_valid_normalized(obj->shape.cone.axis)
		|| !ft_stod_valid(params[3], &obj->shape.cone.diameter)
		|| !ft_stod_valid(params[4], &obj->shape.cone.height)
		|| !parse_color(params[color_idx], &obj->material.color))
	{
		free_split(params);
		return (ft_puterr("Invalid scene configuration"));
	}
	init_material(&obj->material, obj->material.color);
	parse_material_options(params, color_idx + 1, &obj->material);
	scene->obj_count++;
	free_split(params);
	return (0);
}
