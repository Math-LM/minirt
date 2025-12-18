/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_int.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:33:36 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:40 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_INT_H
# define LIGHTING_INT_H

# include "../render_int.h"

typedef struct s_light_calc
{
	t_vec3	hit_point;
	t_vec3	normal;
	t_vec3	cam_pos;
	t_color	color;
	t_phong	phong;
}			t_light_calc;

t_color		calc_specular(t_light *light, t_light_calc *calc);

#endif