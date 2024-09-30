/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/30 22:07:05 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_parser		*parser;
	t_map_info		*map_info;
	t_map_render	*map;
	t_cub3D			*cub3d;
	t_player			player;

	if (argc != 2)
		ft_error("Error\nInvalid number of arguments");
	check_file_extension(argv[1]);
	cub3d = malloc(sizeof(t_cub3D));
	map_info = malloc(sizeof(t_map_info));
	map = malloc(sizeof(t_map_render));
	if (!cub3d || !map_info || !map)
		ft_error("Error\nMemory allocation failed");
	cub3d->map = map;
	parser = NULL;
	map_analyzer(&parser, map_info, argv[1]);
	parse_map(parser, cub3d);
	cub3d->player = &player;
	init_settings(cub3d);
	render_3d(cub3d);
	mlx_key_hook(cub3d->__mlx, key_handler, cub3d);
	mlx_loop(cub3d->__mlx);
	return (0);
}
