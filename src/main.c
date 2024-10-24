/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/18 22:54:38 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	run_animation(t_cub3d *cub)
{
	static int		i;

	if (i % 2 == 0)
	{
		mlx_delete_image(cub->__mlx, cub->tp);
		cub->tp = mlx_texture_to_image(cub->__mlx, cub->sprit_text[cub->fram]);
		mlx_image_to_window(cub->__mlx, cub->tp, 0, 0);
		if (!cub->animation_flage && cub->fram == 179)
			cub->fram = 150;
		if (cub->animation_flage && cub->fram == 179)
		{
			cub->fram = 150;
			cub->animation_flage = 0;
		}
		cub->fram++;
	}
	i++;
}

void	fram(void *params)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)params;
	ft_clear_image(cub->__img);
	move_player(cub);
	open_door_animation(cub);
	close_door_animation(cub);
	render_3d(cub);
	run_animation(cub);
}

void	init_texture(t_cub3d *cub)
{
	mlx_texture_t	*intro;
	mlx_texture_t	*door;

	intro = my_mlx_load_png("intro.png", cub);
	door = my_mlx_load_png("door.png", cub);
	cub->intro_img = my_mlx_texture_to_img(cub, intro);
	cub->door_img = my_mlx_texture_to_img(cub, door);
}

void	init_data(t_cub3d *cub3d)
{
	t_door			*door;

	door = NULL;
	init_settings(cub3d);
	init_texture(cub3d);
	init_wall_texture(cub3d);
	get_door_info(cub3d, &door);
	load_sprit_texture(cub3d);
	cub3d->doors = door;
	mlx_image_to_window(cub3d->__mlx, cub3d->__img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_parser		*parser;
	t_map_info		*map_info;
	t_map_render	*map;
	t_cub3d			*cub3d;
	t_player		player;

	if (argc != 2)
		ft_error("Error\nInvalid number of arguments");
	check_file_extension(argv[1]);
	cub3d = o_malloc(sizeof(t_cub3d), 0);
	map_info = o_malloc(sizeof(t_map_info), 0);
	map = o_malloc(sizeof(t_map_render), 0);
	cub3d->map = map;
	parser = NULL;
	map_analyzer(&parser, map_info, argv[1]);
	parse_map(parser, cub3d);
	cub3d->map->map_info = map_info;
	cub3d->player = &player;
	init_data(cub3d);
	mlx_key_hook(cub3d->__mlx, key_handler, cub3d);
	mlx_cursor_hook(cub3d->__mlx, mouse_handler, cub3d);
	mlx_loop_hook(cub3d->__mlx, fram, cub3d);
	mlx_loop(cub3d->__mlx);
	return (0);
}
