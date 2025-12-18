/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:29:20 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:43:10 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_INT_H
# define RENDER_INT_H

# include "minirt.h"

// Image plane for ray generation
typedef struct s_viewport
{
	double		width; // Physical width in world units
	double		height; // Physical height in world units
	double		distance; // Distance from camera to plane center
	t_vec3		horizontal; // Full width vector (right * width)
	t_vec3		vertical; // Full height vector (up * height)
	t_vec3		lower_left; // World position of lower-left corner
}				t_viewport;

typedef struct s_ray
{
	t_vec3		origin; // Camera position
	t_vec3		direction; // Normalized direction vector
}				t_ray;

typedef struct s_hit
{
	int			hit; // Did we hit something?
	double		t; // Distance along ray
	t_vec3		point; // Hit point in world space
	t_vec3		normal; // Surface normal at hit point
	t_object	*object; // Which object was hit
}				t_hit;

/* Closest Hit */
t_hit			find_closest_hit(t_ray *ray, t_scene *scene);

/* Lighting */
t_color			calculate_lighting(t_scene *scene, t_hit *hit, t_vec3 cam_pos,
					void *mlx);

/* Texture BONUS */
t_color			get_texture_color(t_hit *hit);

/* Pattern BONUS */
t_color			get_pattern_color(t_hit *hit);

/* Bump BONUS */
t_vec3			apply_bump_map(void *mlx, t_hit *hit);

#endif