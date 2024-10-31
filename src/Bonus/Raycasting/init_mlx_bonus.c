/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:05:40 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/25 17:45:32 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_wall_texture(t_cub3d *cub)
{
	mlx_texture_t	*texture[4];

	texture[0] = my_mlx_load_png \
	(ft_strtrim(cub->map->map_info->no_texture, "\n"), cub);
	texture[1] = my_mlx_load_png \
	(ft_strtrim(cub->map->map_info->so_texture, "\n"), cub);
	texture[2] = my_mlx_load_png \
	(ft_strtrim(cub->map->map_info->ea_texture, "\n"), cub);
	texture[3] = my_mlx_load_png \
	(ft_strtrim(cub->map->map_info->we_texture, "\n"), cub);
	cub->texture_no = texture[0];
	cub->texture_so = texture[1];
	cub->texture_ea = texture[2];
	cub->texture_we = texture[3];
	cub->texture_img_ea = my_mlx_texture_to_img(cub, cub->texture_ea);
	cub->texture_img_we = my_mlx_texture_to_img(cub, cub->texture_we);
	cub->texture_img_so = my_mlx_texture_to_img(cub, cub->texture_so);
	cub->texture_img_no = my_mlx_texture_to_img(cub, cub->texture_no);
}

void	init_mlx(t_cub3d *cub)
{
	t_door	*door;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub->screen_height = cub->max_height * T_L;
	cub->screen_width = cub->max_width * T_L;
	cub->__mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	cub->rays = o_malloc(sizeof(t_ray) * SCREEN_WIDTH, 0);
	door = o_malloc(sizeof(t_door), 0);
	door->is_open = 0;
	door->is_opening = 0;
	door->progress = 1;
	door->is_facingx = 1;
	cub->doors = door;
	if (!cub->__mlx || !cub->rays)
	{
		printf("%s\n", mlx_strerror(MLX_WINFAIL));
		exit(1);
	}
	cub->__img = mlx_new_image(cub->__mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub->__img)
	{
		printf("%s\n", mlx_strerror(MLX_INVIMG));
		o_malloc(0, 1);
		exit(1);
	}
}

void	set_player_pos(t_cub3d *cub)
{
	int			x;
	int			y;
	t_parser	*tmp;

	tmp = cub->parser;
	y = 0;
	while (tmp->next)
	{
		x = -1;
		while (tmp->line[++x])
		{
			if (player_character(tmp->line[x]))
			{
				cub->player->pos.x = (double)x * T_L + (T_L / 2);
				cub->player->pos.y = (double)y * T_L + (T_L / 2);
				cub->player->player_character = tmp->line[x];
				return ;
			}
		}
		y++;
		tmp = tmp->next;
	}
}

void	init_player(t_player *player)
{
	if (player->player_character == 'N')
		player->angle = 270 * (M_PI / 180);
	else if (player->player_character == 'S')
		player->angle = 90 * (M_PI / 180);
	else if (player->player_character == 'W')
		player->angle = 180 * (M_PI / 180);
	else if (player->player_character == 'E')
		player->angle = 0;
	player->prev_x = player->pos.x;
	player->walk_direction = 0;
	player->turn_direction = 0;
	player->arrow = 0;
}

void	init_settings(t_cub3d *cub)
{
	init_mlx(cub);
	cub->fov = 60 * (M_PI / 180);
	cub->animation_flage = 0;
	cub->fram = 150;
	set_player_pos(cub);
	init_player(cub->player);
	get_minimap_scale(cub);
}
