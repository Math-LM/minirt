/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:00:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:23:30 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft_conversion.h"
#include "lft_string.h"
#include "parser_int.h"

static void	parse_bump_option(char *value, t_object *obj)
{
	char	**parts;

	parts = ft_split(value, ",");
	if (!parts || !parts[0])
	{
		free_split(parts);
		return ;
	}
	obj->bump.enabled = 1;
	obj->bump.path = ft_strdup(parts[0]);
	obj->bump_scale = 1.0;
	if (parts[1])
		ft_stod_valid(parts[1], &obj->bump_scale);
	free_split(parts);
}

static void	parse_texture_option(char *value, t_object *obj)
{
	obj->texture.enabled = 1;
	obj->texture.path = ft_strdup(value);
}

void	parse_material_options(char **params, int start_idx, t_object *obj)
{
	int		i;
	char	*colon;

	i = start_idx;
	while (params[i])
	{
		colon = ft_strchr(params[i], ':');
		if (colon)
		{
			*colon = '\0';
			if (ft_strcmp(params[i], "pat") == 0)
			{
				ft_stod_valid(colon + 1, &obj->check.scale);
				obj->check.enabled = 1;
			}
			else if (ft_strcmp(params[i], "bum") == 0)
				parse_bump_option(colon + 1, obj);
			else if (ft_strcmp(params[i], "txm") == 0)
				parse_texture_option(colon + 1, obj);
		}
		i++;
	}
}
