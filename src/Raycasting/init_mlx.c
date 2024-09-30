/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:05:40 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/30 18:22:37 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    init_mlx(t_cub3D *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	// mlx_set_setting(MLX_FULLSCREEN, true);
	cub->screen_height = cub->max_height * TILE_SIZE;
	cub->screen_width = cub->max_width * TILE_SIZE;
	cub->__mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", false);
	cub->rays = malloc(sizeof(t_Ray) * cub->screen_width);
	if (!cub->__mlx || !cub->rays)
	{
		printf("%s\n", mlx_strerror(MLX_WINFAIL));
		exit(1);
	}
}

void    set_player_pos(t_cub3D *cub)
{
	int x;
	int y;

	y = 0;
	while (y < cub->max_height)
	{
		x = 0;
		while (x < cub->max_width)
		{
			if (player_character(cub->map->map[y][x]))
			{
				cub->player->pos.x = (double)x * TILE_SIZE + (TILE_SIZE / 2);
				cub->player->pos.y = (double)y * TILE_SIZE + (TILE_SIZE / 2);
			}
			x++;
		}
		y++;
	}
}

void    init_player(t_player *player)
{
	player->angle = NORD;
	player->rot_speed = 100;     
}

void    init_settings(t_cub3D *cub)
{
	init_mlx(cub);
	set_player_pos(cub);
	init_player(cub->player);
}
