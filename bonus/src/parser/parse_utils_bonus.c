/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:25:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 17:29:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_int_bonus.h"

int	parse_vec3(char *str, t_vec3 *vec)
{
	char	**coords;
	int		result;

	coords = ft_split(str, ",");
	if (!coords || !coords[0] || !coords[1] || !coords[2] || coords[3])
	{
		free_split(coords);
		return (0);
	}
	result = 1;
	if (!ft_stod_valid(coords[0], &vec->x) || !ft_stod_valid(coords[1], &vec->y)
		|| !ft_stod_valid(coords[2], &vec->z))
		result = 0;
	free_split(coords);
	return (result);
}

int	parse_color(char *str, t_color *color)
{
	char	**rgb;
	char	*semicolon;
	int		result;
	int		r;
	int		g;
	int		b;

	semicolon = ft_strchr(str, ';');
	if (semicolon)
		*semicolon = '\0';
	rgb = ft_split(str, ",");
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_split(rgb);
		return (0);
	}
	result = 1;
	if (!ft_atoi_valid(rgb[0], &r) || !ft_atoi_valid(rgb[1], &g)
		|| !ft_atoi_valid(rgb[2], &b))
		result = 0;
	else
	{
		color->r = r;
		color->g = g;
		color->b = b;
		if (!is_valid_color(*color))
			result = 0;
	}
	free_split(rgb);
	return (result);
}

char	*skip_spaces(char *s)
{
	while (*s && (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r'))
		s++;
	return (s);
}
