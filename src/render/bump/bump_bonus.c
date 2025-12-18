/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:40:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 14:11:07 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bump_int_bonus.h"
#include "mlx.h"

static double	get_bump_height(void *img, int x, int y, int wh[2])
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		color;

	if (x < 0)
		x = 0;
	if (x >= wh[0])
		x = wh[0] - 1;
	if (y < 0)
		y = 0;
	if (y >= wh[1])
		y = wh[1] - 1;
	addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
	color = *(int *)(addr + y * line_len + x * (bpp / 8));
	return (((color >> 16) & 0xFF) / 255.0);
}

static void	compute_bump_uv(t_hit *hit, double *u, double *v)
{
	if (hit->object->type == OBJ_SPHERE)
		get_sphere_bump_uv(hit, u, v);
	else if (hit->object->type == OBJ_PLANE)
		get_plane_bump_uv(hit, u, v);
	else if (hit->object->type == OBJ_CYLINDER)
		get_cylinder_bump_uv(hit, u, v);
	else if (hit->object->type == OBJ_CONE)
		get_cone_bump_uv(hit, u, v);
}

static void	get_bump_heights(t_hit *hit, int xy[2], int wh[2], double h[3])
{
	h[0] = get_bump_height(hit->object->bump.img, xy[0], xy[1], wh);
	h[1] = get_bump_height(hit->object->bump.img, xy[0] + 1, xy[1],
			wh);
	h[2] = get_bump_height(hit->object->bump.img, xy[0], xy[1] + 1,
			wh);
}

t_vec3	apply_bump_map(void *mlx, t_hit *hit)
{
	int		wh[2];
	double	uv[2];
	double	height[3];
	int		xy[2];

	(void)mlx;
	if (!hit->object->bump.enabled || !hit->object->bump.img)
		return (hit->normal);
	wh[0] = hit->object->bump.width;
	wh[1] = hit->object->bump.height;
	compute_bump_uv(hit, &uv[0], &uv[1]);
	if (hit->object->type != OBJ_SPHERE && hit->object->type != OBJ_PLANE
		&& hit->object->type != OBJ_CYLINDER && hit->object->type != OBJ_CONE)
		return (hit->normal);
	xy[0] = (int)(uv[0] * wh[0]);
	xy[1] = (int)(uv[1] * wh[1]);
	get_bump_heights(hit, xy, wh, height);
	return (perturb_normal(hit->normal, height,
			hit->object->bump_scale));
}
