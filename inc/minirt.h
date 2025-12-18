/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:28:29 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:40:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "object.h"
# include <stdio.h> // DEBUG

# define WIDHT 1600
# define HEIGHT 900

# define MAX_LIGHTS 10
# define MAX_OBJECTS 100

typedef struct s_ambient
{
	double		ratio;
	t_color		color;
	int			set;
}				t_ambient;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		orient;
	int			fov;
	int			set;
}				t_camera;

typedef struct s_light
{
	t_vec3		pos;
	double		brightness;
	t_color		color; // BONUS
}				t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		lights[MAX_LIGHTS]; // BONUS
	int			light_count; // BONUS
	t_object	objects[MAX_OBJECTS];
	int			obj_count;
}				t_scene;

/* Parser */
void			parse_scene(char *filepath, t_scene *scene);

/* Render */
struct	s_mlx;
void			render_scene(t_scene *scene, struct s_mlx *mlx);

#endif