/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:30:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 09:43:05 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_int.h"

int	is_valid_normalized(t_vec3 vec)
{
	if (vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0)
		return (0);
	return (1);
}

int	is_valid_color(t_color color)
{
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		return (0);
	return (1);
}

int	is_valid_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}
