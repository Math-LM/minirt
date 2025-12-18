/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-alm <joao-alm@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:00:45 by joao-alm          #+#    #+#             */
/*   Updated: 2025/12/18 15:18:29 by joao-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lft_error.h"
#include "lft_string.h"
#include "minirt.h"
#include "mlx_util.h"
#include <stdlib.h>

void	handle_args(int ac, char **av)
{
	size_t	file_len;

	if (ac != 2)
		exit(put_error_msg("Usage: ./miniRT_bonus scene_file.rt"));
	file_len = ft_strlen(av[1]);
	if (file_len < 3 || ft_strcmp(av[1] + file_len - 3, ".rt") != 0)
		exit(put_error_msg("Scene file must be of type .rt"));
}

int	main(int ac, char **av)
{
	t_scene	scene;
	t_mlx	mlx;

	handle_args(ac, av);
	parse_scene(av[1], &scene);
	ft_init_mlx(&scene, &mlx);
	render_scene(&scene, &mlx);
	keyhook(&scene, &mlx);
	mlx_loop(mlx.ptr);
	ft_cleanup_mlx(&scene, &mlx);
	return (0);
}
