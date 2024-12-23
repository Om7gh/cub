/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:31:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/11/01 21:47:57 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	put_pixel_map(int x, int y, int color, t_cub3d *cub)
{
	if (x >= 150 || x < 0 || y >= 150 || y < 0)
		return ;
	mlx_put_pixel(cub->__img, x, y, color);
}

void	draw_player(t_cub3d *cub)
{
	int		x;
	int		y;

	y = -1;
	while (++y < 6)
	{
		x = -1;
		while (++x < 6)
			put_pixel_map(71 + x, 71 + y, ORANGE, cub);
	}
}

void	mini_map_background(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (++y <= 150)
	{
		x = -1;
		while (++x <= 150)
			put_pixel_map(x, y, 0, cub);
		my_mlx_put_pixel(x, y, WHITE, cub);
	}
	x = -1;
	while (++x <= 150)
		my_mlx_put_pixel(x, y, WHITE, cub);
}

void	render_minimap(t_cub3d *cub)
{
	int	x;
	int	y;

	y = -1;
	mini_map_background(cub);
	while (++y < cub->screen_height / 4)
	{
		x = -1;
		while (++x < cub->screen_width / 4)
		{
			if (cub->map->map[(int)(y * 4 / T_L)] \
			[(int)(x * 4 / T_L)] == 1)
				put_pixel_map(x - cub->player->pos.x / 4 + 75, \
					y - cub->player->pos.y / 4 + 75, CRIMSON, cub);
			else if (cub->map->map[(int)(y * 4 / T_L)] \
			[(int)(x * 4 / T_L)] == 3)
				put_pixel_map(x - cub->player->pos.x / 4 + 75, \
					y - cub->player->pos.y / 4 + 75, ORANGE, cub);
			else
				put_pixel_map(x - cub->player->pos.x / 4 + 75, \
					y - cub->player->pos.y / 4 + 75, BLACK, cub);
		}
	}
	draw_player(cub);
}
