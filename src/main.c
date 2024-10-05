/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/05 20:08:36 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	func(void *params)
{
	t_cub3D *cub;

	cub = (t_cub3D*)params;

	open_door_animation(cub);
	close_door_animation(cub);
	render_3d(cub);
	mlx_image_to_window(cub->__mlx, cub->intro_img, 0, 0);
}

void	get_door_info(t_cub3D *cub, t_door **door)
{
	t_door *new;
	int	x;
	int	y;

	y = 0;
	while (y < cub->max_height)
	{
		x = 0;
		while (x < cub->max_width)
		{
			if (cub->map->map[y][x] == 3)
			{
				new = new_door(y + 1, x + 1);
				fill_door_list(door, new);
			}
			x++;
		}
		y++;
	}
}


void	init_texture(t_cub3D *cub)
{
	mlx_texture_t *text;
	mlx_texture_t *intro;

	text = mlx_load_png("test.png");
	if (!text)
	{
		mlx_terminate(cub->__mlx);
		ft_error("Error loading .png texture.\n");
	}
	intro = mlx_load_png("intro.png");
	if (!intro)
	{
		mlx_terminate(cub->__mlx);
		ft_error("Error loading .png texture.\n");
	}
	cub->texture = text;
	cub->intro = intro;
}

int	main(int argc, char **argv)
{
	t_parser		*parser;
	t_map_info		*map_info;
	t_map_render	*map;
	t_cub3D			*cub3d;
	t_player			player;
	t_door				*door;

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
	door = NULL;
	cub3d->map->map_info = map_info;
	cub3d->player = &player;
	init_settings(cub3d);
	init_texture(cub3d);
	cub3d->texture_img = mlx_texture_to_image(cub3d->__mlx, cub3d->texture);
	if (!cub3d->texture_img)
	{
	    printf("Error converting PNG texture to image.\n");
	    mlx_terminate(cub3d->__mlx);
	    return -1;
	}
	cub3d->intro_img = mlx_texture_to_image(cub3d->__mlx, cub3d->intro);
	if (!cub3d->intro_img)
	{
	    printf("Error converting PNG texture to image.\n");
	    mlx_terminate(cub3d->__mlx);
	    return -1;
	}
	get_door_info(cub3d, &door);
	cub3d->doors = door;
	render_3d(cub3d);
	mlx_key_hook(cub3d->__mlx, key_handler, cub3d);
	mlx_cursor_hook(cub3d->__mlx, mouse_handler, cub3d);
	mlx_loop_hook(cub3d->__mlx, func, cub3d);
	mlx_loop(cub3d->__mlx);
	return (0);
}
