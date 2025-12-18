/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:48:28 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:34:12 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_util.h"
#include "render_int.h"
#include <math.h>

/*
** Initializes the viewport (image plane) based on camera FOV and aspect ratio.
** Computes camera basis vectors (forward, right, up) to orient the viewport.
** The viewport is centered at distance 1.0 from camera along forward direction.
*/
t_viewport	init_viewport(t_camera *cam, int width, int height)
{
	t_viewport	vp;
	double		aspect_ratio;
	t_vec3		cam_vec[3];
	double		theta;

	aspect_ratio = (double)width / height;
	theta = cam->fov * M_PI / 180.0;
	vp.distance = 1.0;
	vp.width = 2.0 * tan(theta / 2) * vp.distance;
	vp.height = vp.width / aspect_ratio;
	vp.width = vp.height * aspect_ratio;
	cam_vec[0] = vec3_normalize(cam->orient);
	cam_vec[1] = vec3_normalize(vec3_cross(vec3_new(0, 1, 0), cam_vec[0]));
	cam_vec[2] = vec3_cross(cam_vec[0], cam_vec[1]);
	vp.horizontal = vec3_scale(cam_vec[1], vp.width);
	vp.vertical = vec3_scale(cam_vec[2], vp.height);
	vp.lower_left = cam->pos;
	vp.lower_left = vec3_add(vp.lower_left, vec3_scale(cam_vec[0],
				vp.distance));
	vp.lower_left = vec3_sub(vp.lower_left, vec3_scale(vp.horizontal, 0.5));
	vp.lower_left = vec3_sub(vp.lower_left, vec3_scale(vp.vertical, 0.5));
	return (vp);
}

/*
** Creates a ray from camera through a specific pixel on the viewport.
** Maps pixel coordinates (x,y) to normalized coords (u,v) on the image plane.
*/
t_ray	create_ray(t_camera *cam, t_viewport *vp, int xy[2], int dimensions[2])
{
	t_ray	ray;
	t_vec3	point;
	double	u;
	double	v;

	u = (double)xy[0] / (dimensions[0] - 1);
	v = (double)(dimensions[1] - 1 - xy[1]) / (dimensions[1] - 1);
	point = vp->lower_left;
	point = vec3_add(point, vec3_scale(vp->horizontal, u));
	point = vec3_add(point, vec3_scale(vp->vertical, v));
	ray.origin = cam->pos;
	ray.direction = vec3_normalize(vec3_sub(point, cam->pos));
	return (ray);
}

static void	render_pixel(t_scene *scene, t_mlx *mlx, t_viewport *vp, int xy[2])
{
	t_ray	ray;
	t_hit	hit;
	t_color	color;

	ray = create_ray(&scene->camera, vp, (int [2]){xy[0], xy[1]},
			(int [2]){mlx->win_width, mlx->win_height});
	hit = find_closest_hit(&ray, scene);
	if (hit.hit)
	{
		color = calculate_lighting(scene, &hit, scene->camera.pos, mlx->ptr);
		set_pixel(&mlx->img, xy[0], xy[1], color_to_int(color));
	}
}

void	render_scene(t_scene *scene, t_mlx *mlx)
{
	t_viewport	vp;
	int			xy[2];

	vp = init_viewport(&scene->camera, mlx->win_width, mlx->win_height);
	ft_init_mlx_img_fullscreen(mlx);
	xy[1] = -1;
	while (++xy[1] < mlx->win_height)
	{
		xy[0] = -1;
		while (++xy[0] < mlx->win_width)
			render_pixel(scene, mlx, &vp, xy);
	}
	ft_mlx_put_img_clean(mlx);
}
