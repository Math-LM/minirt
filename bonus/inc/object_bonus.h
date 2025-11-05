/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:22:20 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 17:27:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_BONUS_H
# define OBJECT_BONUS_H

#include "vec3_bonus.h"
#include "color_bonus.h"

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
}					t_obj_type;

typedef enum e_pattern
{
	PATTERN_NONE,
	PATTERN_CHECKER
}					t_pattern;

typedef struct s_sphere
{
	t_vec3			center;
	double			diameter;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			axis;
	double			diameter;
	double			height;
}					t_cylinder;

typedef struct s_cone
{
	t_vec3			center;
	t_vec3			axis;
	double			diameter;
	double			height;
}					t_cone;

typedef struct s_material
{
	t_color			color;
	double			specular;
	double			shininess;
	t_pattern		pattern;
	double			pat_scale;
	int				pat_type;
}					t_material;

typedef struct s_object
{
	t_obj_type		type;
	t_material		material;
	union			u_shape
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	} shape;
}					t_object;

#endif