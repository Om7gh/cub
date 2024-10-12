/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:56 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 20:59:10 by hbettal          ###   ########.fr       */
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

void	func(void *params)
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

void	get_door_info(t_cub3d *cub, t_door **door)
{
	t_door	*new;
	int		x;
	int		y;

	y = -1;
	while (++y < cub->max_height)
	{
		x = -1;
		while (++x < cub->max_width)
		{
			if (cub->map->map[y][x] == 3)
			{
				new = new_door(x + 1, y + 1);
				if (cub->map->map[y - 1][x] == 1)
					new->is_facingx = 1;
				fill_door_list(door, new);
			}
		}
	}
}

mlx_texture_t	*my_mlx_load_png( const char *path, t_cub3d *cub)
{
	mlx_texture_t	*text;

	text = mlx_load_png(path);
	if (!text)
	{
		mlx_terminate(cub->__mlx);
		ft_error("Error loading .png texture.\n");
	}
	return (text);
}

mlx_image_t	*my_mlx_texture_to_img(t_cub3d *cub, mlx_texture_t *texture)
{
	mlx_image_t	*text_to_img;

	text_to_img = mlx_texture_to_image(cub->__mlx, texture);
	if (!cub->texture_img_no)
	{
		printf("Error converting PNG texture to image.\n");
		mlx_terminate(cub->__mlx);
		o_malloc(0, 1);
		exit(1);
	}
	return (text_to_img);
}

void	init_texture(t_cub3d *cub)
{
	mlx_texture_t *intro;
	mlx_texture_t *door;
	
	intro = my_mlx_load_png("intro.png", cub);
	door = my_mlx_load_png("doot.png", cub);
	cub->intro_img = my_mlx_texture_to_img(cub, intro);
	cub->door_img = my_mlx_texture_to_img(cub, door);
}

void	init_wall_texture(t_cub3d *cub)
{
	mlx_texture_t *text_no;
	mlx_texture_t *text_so;
	mlx_texture_t *text_ea;
	mlx_texture_t *text_we;

	text_no = my_mlx_load_png(ft_strtrim(cub->map->map_info->no_texture, "\n"), cub);
	text_so = my_mlx_load_png(ft_strtrim(cub->map->map_info->so_texture, "\n"), cub);
	text_ea = my_mlx_load_png(ft_strtrim(cub->map->map_info->ea_texture, "\n"), cub);
	text_we = my_mlx_load_png(ft_strtrim(cub->map->map_info->no_texture, "\n"), cub);
	cub->texture_no = text_no;
	cub->texture_so = text_so;
	cub->texture_ea = text_ea;
	cub->texture_we = text_we;
	cub->texture_img_ea = my_mlx_texture_to_img(cub, cub->texture_ea);
	cub->texture_img_we = my_mlx_texture_to_img(cub, cub->texture_we);
	cub->texture_img_so = my_mlx_texture_to_img(cub, cub->texture_so);
	cub->texture_img_no = my_mlx_texture_to_img(cub, cub->texture_no);
}

void	init_enemie_texture(t_cub3d *cub)
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

void	init_data(t_cub3d *cub3d, t_door *door)
{
	init_settings(cub3d);
	init_texture(cub3d);
	init_wall_texture(cub3d);
	init_enemie_texture(cub3d);
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
	t_player			player;
	t_door				*door;

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
	door = NULL;
	cub3d->map->map_info = map_info;
	cub3d->player = &player;
	init_data(cub3d, door);
	mlx_loop_hook(cub3d->__mlx, func, cub3d);
	mlx_loop(cub3d->__mlx);
	o_malloc(0, 1);
	return (0);
}
