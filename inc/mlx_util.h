/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:51:53 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 15:35:24 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTIL_H
# define MLX_UTIL_H

# include "minirt.h"
# include "mlx.h"

# define ESC_KEY 65307

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	int		win_width;
	int		win_height;
	t_img	img;
}			t_mlx;

/* Keyhook */
typedef struct s_keyhook
{
	t_scene	*scene;
	t_mlx	*mlx;
}			t_keyhook;

void		keyhook(t_scene *scene, t_mlx *mlx);

/* Bonus Images */
void		load_textures(t_scene *scene, t_mlx *mlx);
void		cleanup_textures(t_scene *scene, t_mlx *mlx);

/* Util */
void		ft_init_mlx(t_scene *scene, t_mlx *mlx);
void		ft_init_mlx_img_fullscreen(t_mlx *mlx);
void		set_pixel(t_img *img, int x, int y, int color);
void		ft_mlx_put_img_clean(t_mlx *mlx);
void		ft_cleanup_mlx(t_scene *scene, t_mlx *mlx);

#endif