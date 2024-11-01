/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:31:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/11/01 15:47:41 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void	draw_rays(t_cub3d *cub)
// {
// 	int		x;
// 	t_vect	from;
// 	t_vect	to;

// 	x = -1;
// 	while (++x < SCREEN_WIDTH)
// 	{
// 		from.x = cub->player->pos.x * cub->scale;
// 		from.y = cub->player->pos.y * cub->scale;
// 		to.x = cub->rays[x].wall_hit.x * cub->scale;
// 		to.y = cub->rays[x].wall_hit.y * cub->scale;
// 		bresenhams(from, to, cub, RED);
// 	}
// }

void	render_minimap(t_cub3d *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < cub->screen_height * cub->scale)
	{
		x = -1;
		while (++x < cub->screen_width * cub->scale)
		{
			if (cub->map->map[(int)(y / cub->scale / T_L)] \
			[(int)(x / cub->scale / T_L)] == 1)
				my_mlx_put_pixel(x, y, WHITE, cub);
			else if (cub->map->map[(int)(y / cub->scale / T_L)] \
			[(int)(x / cub->scale / T_L)] == 3)
				my_mlx_put_pixel(x, y, ORANGE, cub);
			else
				my_mlx_put_pixel(x, y, BLACK, cub);
		}
	}
	// draw_rays(cub);
}
