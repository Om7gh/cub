/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 10:22:15 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    move_player(t_cub3D *cub)
{
	t_vect next_pos;
	double next_angle;
	
	next_pos.x = cub->player->pos.x + SPEED * cos(cub->player->angle) * cub->player->walk_direction;
	next_pos.y = cub->player->pos.y + SPEED * sin(cub->player->angle) * cub->player->walk_direction;
	next_angle = cub->player->angle + ROTATION_SPEED * cub->player->turn_direction;
	cub->player->angle = next_angle;
	cub->player->angle = remainder(cub->player->angle, 2 * M_PI);
	if (cub->player->angle < 0)
		cub->player->angle += 2 * M_PI;
	if (!wall(cub, next_pos.x + 5, next_pos.y) && !wall(cub, next_pos.x - 5, next_pos.y))
	{
		cub->player->pos.x = next_pos.x;
		cub->player->pos.y = next_pos.y;
	}
	if (cub->player->arrow != 0)
	{
		next_pos.x = cub->player->pos.x + SPEED * cos(cub->player->angle + M_PI / 2) * cub->player->arrow;
		next_pos.y = cub->player->pos.y + SPEED * sin(cub->player->angle + M_PI / 2) * cub->player->arrow;
		if (!wall(cub, next_pos.x + 5, next_pos.y) && !wall(cub, next_pos.x - 5, next_pos.y))
		{
			cub->player->pos.x = next_pos.x;
			cub->player->pos.y = next_pos.y;
		}
	}
}

void	func(void *params)
{
	t_cub3D *cub;

	cub = (t_cub3D*)params;
	if (cub->__img)
		mlx_delete_image(cub->__mlx, cub->__img);
	cub->__img = mlx_new_image(cub->__mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	move_player(cub);
	open_door_animation(cub);
	close_door_animation(cub);
	render_3d(cub);
	mlx_image_to_window(cub->__mlx, cub->__img, 0, 0);
}

void	get_door_info(t_cub3D *cub, t_door **door)
{
	t_door *new;
	t_sprite	*sprite;
	int	x;
	int	y;

	sprite = o_malloc(sizeof(t_sprite), 0);
	y = 0;
	while (y < cub->max_height)
	{
		x = 0;
		while (x < cub->max_width)
		{
			if (cub->map->map[y][x] == 3)
			{
				new = new_door(x + 1, y + 1);
				if (cub->map->map[y - 1][x] == 1)
					new->is_facingx = 1;
				fill_door_list(door, new);
			}
			if (cub->map->map[y][x] == 4)
			{
				sprite->x = x;
				sprite->y = y;
			}
			x++;
		}
		y++;
	}
	cub->sprites = sprite;
}

void	init_texture(t_cub3D *cub)
{
	mlx_texture_t *text;
	mlx_texture_t *intro;
	mlx_texture_t *door;

	text = mlx_load_png("wall.png");
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
	door = mlx_load_png("doot.png");
	if (!intro)
	{
		mlx_terminate(cub->__mlx);
		ft_error("Error loading .png texture.\n");
	}
	cub->texture = text;
	cub->intro = intro;
	cub->door_texture = door;
}

void	init_enemie_texture(t_cub3D *cub)
{
	t_enemie	*enemie;
	t_enemie	*new;

	enemie = NULL;
	new = new_enemie("enemie/enemie1.png", cub);
	append_enemie(&enemie, new);
	new = new_enemie("enemie/enemie2.png", cub);
	append_enemie(&enemie, new);
	new = new_enemie("enemie/enemie3.png", cub);
	append_enemie(&enemie, new);
	new = new_enemie("enemie/enemie4.png", cub);
	append_enemie(&enemie, new);
	cub->enemie = enemie;
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
	cub3d = o_malloc(sizeof(t_cub3D), 0);
	map_info = o_malloc(sizeof(t_map_info), 0);
	map = o_malloc(sizeof(t_map_render), 0);
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
	    o_malloc(0, 1);
	    return -1;
	}
	cub3d->intro_img = mlx_texture_to_image(cub3d->__mlx, cub3d->intro);
	if (!cub3d->intro_img)
	{
	    printf("Error converting PNG texture to image.\n");
	    mlx_terminate(cub3d->__mlx);
	    o_malloc(0, 1);
	    return -1;
	}
	cub3d->door_img = mlx_texture_to_image(cub3d->__mlx, cub3d->door_texture);
	if (!cub3d->door_img)
	{
	    printf("Error converting PNG texture to image.\n");
	    mlx_terminate(cub3d->__mlx);
	    o_malloc(0, 1);
	    return -1;
	}
	init_enemie_texture(cub3d);
	get_door_info(cub3d, &door);
	cub3d->doors = door;
	render_3d(cub3d);
	mlx_key_hook(cub3d->__mlx, key_handler, cub3d);
	mlx_cursor_hook(cub3d->__mlx, mouse_handler, cub3d);
	mlx_loop_hook(cub3d->__mlx, func, cub3d);
	mlx_loop(cub3d->__mlx);
	return (0);
}
