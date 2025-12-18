/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:22:20 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/15 19:30:29 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "color.h"
# include "object_bonus.h" // BONUS
# include "vec3.h"

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE // BONUS
}					t_obj_type;

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

typedef struct s_object
{
	t_obj_type		type;
	t_color			color;
	t_phong			phong; // BONUS
	t_checkboard	check; // BONUS
	t_texture		texture; // BONUS
	t_texture		bump; // BONUS
	double			bump_scale; // BONUS
	union			u_shape
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone; // BONUS
	} shape;
}					t_object;

#endif