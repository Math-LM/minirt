/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_int_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:07:24 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 14:10:09 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUMP_INT_BONUS_H
#define BUMP_INT_BONUS_H

#include "../render_int.h"

/* Normal */
t_vec3	perturb_normal(t_vec3 normal, double height[3], double scale);

/* UV's */
void	get_sphere_bump_uv(t_hit *hit, double *u, double *v);
void	get_plane_bump_uv(t_hit *hit, double *u, double *v);
void	get_cylinder_bump_uv(t_hit *hit, double *u, double *v);
void	get_cone_bump_uv(t_hit *hit, double *u, double *v);

#endif