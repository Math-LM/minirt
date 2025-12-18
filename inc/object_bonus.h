/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:22:20 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/15 19:29:58 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_BONUS_H
# define OBJECT_BONUS_H

# include "vec3.h"

typedef struct s_cone
{
	t_vec3	center;
	t_vec3	axis;
	double	diameter;
	double	height;
}			t_cone;

typedef struct s_phong
{
	double	specular;
	double	shininess;
}			t_phong;

typedef struct s_checkboard
{
	int		enabled;
	double	scale;
}			t_checkboard;

typedef struct s_texture
{
	int		enabled;
	char	*path;
	void	*img;
	int		width;
	int		height;
}			t_texture;

#endif