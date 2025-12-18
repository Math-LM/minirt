/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_int.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:01:31 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 13:51:58 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INT_H
# define PARSER_INT_H

# include "minirt.h"

/* Parse elements */
int		parse_ambient(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);

/* Parse objects */
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_cone(char *line, t_scene *scene);

/* Parse utils */
void	init_phong(t_object *obj); // BONUS
int		parse_vec3(char *str, t_vec3 *vec);
int		parse_color(char *str, t_color *color);
char	*skip_spaces(char *s);

/* Parse options */
void	parse_material_options(char **params, int start_idx, t_object *obj);

/* Parse validation */
int		is_valid_normalized(t_vec3 vec);
int		is_valid_color(t_color color);
int		is_valid_range(double value, double min, double max);

#endif