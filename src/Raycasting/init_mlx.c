/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:05:40 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 13:46:42 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_mlx(t_cub3D *cub)
{
	t_door	*door;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub->screen_height = cub->max_height * T_L;
	cub->screen_width = cub->max_width * T_L;
	cub->__mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", true);
	cub->rays = o_malloc(sizeof(t_Ray) * SCREEN_WIDTH, 0);
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

void	set_player_pos(t_cub3D *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->max_height)
	{
		x = -1;
		while (++x < cub->max_width)
		{
			if (player_character(cub->map->map[y][x]))
			{
				cub->player->pos.x = (double)x * T_L + (T_L / 2);
				cub->player->pos.y = (double)y * T_L + (T_L / 2);
				return ;
			}
		}
	}
}

void	init_player(t_player *player)
{
	player->angle = NORD;
	player->prev_x = player->pos.x;
	player->walk_direction = 0;
	player->turn_direction = 0;
	player->arrow = 0;
}

void	init_settings(t_cub3D *cub)
{
	init_mlx(cub);
	set_player_pos(cub);
	init_player(cub->player);
}
