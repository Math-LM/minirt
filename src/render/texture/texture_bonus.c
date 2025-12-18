/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:24:50 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "texture_int_bonus.h"

static void	compute_texture_uv(t_hit *hit, double *u, double *v)
{
	if (hit->object->type == OBJ_SPHERE)
		get_sphere_tex_uv(hit, u, v);
	else if (hit->object->type == OBJ_PLANE)
		get_plane_tex_uv(hit, u, v);
	else if (hit->object->type == OBJ_CYLINDER)
		get_cylinder_tex_uv(hit, u, v);
	else if (hit->object->type == OBJ_CONE)
		get_cone_tex_uv(hit, u, v);
}

static t_color	sample_texture_at(void *img, int x, int y, int wh[2])
{
	char	*addr;
	int		params[3];
	int		pixel;
	t_color	color;

	if (x < 0)
		x = 0;
	if (x >= wh[0])
		x = wh[0] - 1;
	if (y < 0)
		y = 0;
	if (y >= wh[1])
		y = wh[1] - 1;
	addr = mlx_get_data_addr(img, &params[0], &params[1], &params[2]);
	pixel = *(int *)(addr + y * params[1] + x * (params[0] / 8));
	color.r = (pixel >> 16) & 0xFF;
	color.g = (pixel >> 8) & 0xFF;
	color.b = pixel & 0xFF;
	return (color);
}

t_color	get_texture_color(t_hit *hit)
{
	double	uv[2];
	int		xy[2];
	int		wh[2];

	if (!hit->object->texture.enabled || !hit->object->texture.img)
		return (hit->object->color);
	wh[0] = hit->object->texture.width;
	wh[1] = hit->object->texture.height;
	compute_texture_uv(hit, &uv[0], &uv[1]);
	if (hit->object->type != OBJ_SPHERE && hit->object->type != OBJ_PLANE
		&& hit->object->type != OBJ_CYLINDER && hit->object->type != OBJ_CONE)
		return (hit->object->color);
	xy[0] = (int)(uv[0] * wh[0]);
	xy[1] = (int)(uv[1] * wh[1]);
	return (sample_texture_at(hit->object->texture.img, xy[0], xy[1], wh));
}
