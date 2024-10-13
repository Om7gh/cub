/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/13 17:13:58 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	move_player(t_cub3d *cub)
{
	t_vect	next_pos;
	double	next_angle;

	next_pos.x = cub->player->pos.x + SPEED * \
	cos(cub->player->angle) * cub->player->walk_direction;
	next_pos.y = cub->player->pos.y + SPEED * \
	sin(cub->player->angle) * cub->player->walk_direction;
	next_angle = cub->player->angle + \
	ROTATION_SPEED * cub->player->turn_direction;
	cub->player->angle = next_angle;
	if (!wall(cub, next_pos.x + 5, next_pos.y) && \
	!wall(cub, next_pos.x - 5, next_pos.y))
		cub->player->pos = next_pos;
	if (cub->player->arrow != 0)
	{
		next_pos.x = cub->player->pos.x + SPEED * \
		cos(cub->player->angle + M_PI / 2) * cub->player->arrow;
		next_pos.y = cub->player->pos.y + SPEED * \
		sin(cub->player->angle + M_PI / 2) * cub->player->arrow;
		if (!wall(cub, next_pos.x + 5, next_pos.y) && \
		!wall(cub, next_pos.x - 5, next_pos.y))
			cub->player->pos = next_pos;
	}
}

void	fram(void *params)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)params;
	if (cub->__img)
		mlx_delete_image(cub->__mlx, cub->__img);
	cub->__img = mlx_new_image(cub->__mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	move_player(cub);
	open_door_animation(cub);
	close_door_animation(cub);
	render_3d(cub);
	mlx_image_to_window(cub->__mlx, cub->__img, 0, 0);
}

void	init_texture(t_cub3d *cub)
{
	mlx_texture_t	*intro;
	mlx_texture_t	*door;

	intro = my_mlx_load_png("intro.png", cub);
	door = my_mlx_load_png("doot.png", cub);
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
	cub3d->doors = door;
	render_3d(cub3d);
	mlx_key_hook(cub3d->__mlx, key_handler, cub3d);
	mlx_cursor_hook(cub3d->__mlx, mouse_handler, cub3d);
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
	mlx_loop_hook(cub3d->__mlx, fram, cub3d);
	mlx_loop(cub3d->__mlx);
	o_malloc(0, 1);
	return (0);
}
