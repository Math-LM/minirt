/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:00:00 by joao-alm          #+#    #+#             */
/*   Updated: 2025/11/05 17:27:43 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "scene_bonus.h"

static int	parse_pattern_option(char *value, t_material *mat)
{
	char	**parts;
	int		result;

	parts = ft_split(value, ",");
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		free_split(parts);
		return (0);
	}
	result = 1;
	if (!ft_stod_valid(parts[0], &mat->pat_scale)
		|| !ft_atoi_valid(parts[1], &mat->pat_type))
		result = 0;
	else
		mat->pattern = PATTERN_CHECKER;
	free_split(parts);
	return (result);
}

void	parse_material_options(char **params, int start_idx, t_material *mat)
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
				parse_pattern_option(colon + 1, mat);
		}
		i++;
	}
}
