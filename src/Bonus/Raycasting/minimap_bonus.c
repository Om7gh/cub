/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:31:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/11/01 17:07:30 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
			put_pixel_map(71 + x, 71 + y, RED, cub);
	}
}

void	render_minimap(t_cub3d *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->screen_height / 4)
	{
		x = -1;
		while (++x < cub->screen_width / 4)
		{
			if (cub->map->map[(int)(y * 4 / T_L)] \
			[(int)(x * 4 / T_L)] == 1)
				put_pixel_map(x - cub->player->pos.x / 4 + 75, y - cub->player->pos.y / 4 + 75, WHITE, cub);
			else if (cub->map->map[(int)(y * 4 / T_L)] \
			[(int)(x * 4 / T_L)] == 3)
				put_pixel_map(x - cub->player->pos.x / 4 + 75, y - cub->player->pos.y / 4 + 75, ORANGE, cub);
			else
				put_pixel_map(x - cub->player->pos.x / 4 + 75, y - cub->player->pos.y / 4 + 75, BLACK, cub);
		}
	}
	draw_player(cub);
}
