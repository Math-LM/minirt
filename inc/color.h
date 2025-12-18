/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:20:44 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/15 18:37:42 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

t_color	color_new(int r, int g, int b);
t_color	color_scale(t_color c, double factor);
t_color	color_add(t_color a, t_color b);
t_color	color_multiply(t_color a, t_color b);
t_color	color_clamp(t_color c);
int		color_to_int(t_color c);

#endif