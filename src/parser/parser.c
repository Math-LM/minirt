/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:01:22 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 16:23:44 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft_error.h"
#include "lft_gnl.h"
#include "lft_memory.h"
#include "lft_string.h"
#include "parser_int.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	parse_line(char *line, t_scene *scene)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!trimmed || !*trimmed || *trimmed == '#')
		return (0);
	if (trimmed[0] == 'A' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (parse_ambient(trimmed, scene));
	if (trimmed[0] == 'C' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (parse_camera(trimmed, scene));
	if (trimmed[0] == 'L' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (parse_light(trimmed, scene));
	if (trimmed[0] == 's' && trimmed[1] == 'p' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_sphere(trimmed, scene));
	if (trimmed[0] == 'p' && trimmed[1] == 'l' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_plane(trimmed, scene));
	if (trimmed[0] == 'c' && trimmed[1] == 'y' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_cylinder(trimmed, scene));
	if (trimmed[0] == 'c' && trimmed[1] == 'o' && (trimmed[2] == ' '
			|| trimmed[2] == '\t'))
		return (parse_cone(trimmed, scene));
	return (put_error_msg("Invalid scene line"));
}

static char	**read_file(char *filepath)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		exit(put_error_msg("Failed to open scene file"));
	lines = malloc(sizeof(char *) * 1000);
	if (!lines)
		exit(put_error_msg("Memory allocation failed"));
	count = 0;
	line = get_next_line(fd);
	while (line && count <= 1000)
	{
		lines[count++] = line;
		line = get_next_line(fd);
	}
	lines[count] = NULL;
	close(fd);
	return (lines);
}

static void	validate_scene(t_scene *scene)
{
	if (!scene->ambient.set)
		exit(put_error_msg("Missing ambient lighting definition"));
	if (!scene->camera.set)
		exit(put_error_msg("Missing camera definition"));
	if (scene->light_count == 0)
		exit(put_error_msg("At least one light is required"));
}

void	parse_scene(char *filepath, t_scene *scene)
{
	char	**lines;
	int		i;

	ft_bzero(scene, sizeof(t_scene));
	lines = read_file(filepath);
	i = 0;
	while (lines[i])
	{
		if (parse_line(lines[i], scene) != 0)
		{
			free_split(lines);
			exit(1);
		}
		i++;
	}
	free_split(lines);
	validate_scene(scene);
}
