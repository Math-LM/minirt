/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_int_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:02:01 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:53 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_INT_BONUS_H
# define TEXTURE_INT_BONUS_H

# include "../render_int.h"

/* UV's */
void	get_sphere_tex_uv(t_hit *hit, double *u, double *v);
void	get_plane_tex_uv(t_hit *hit, double *u, double *v);
void	get_cylinder_tex_uv(t_hit *hit, double *u, double *v);
void	get_cone_tex_uv(t_hit *hit, double *u, double *v);

#endif