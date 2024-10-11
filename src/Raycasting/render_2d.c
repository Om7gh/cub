/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:56:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/10 12:08:26 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    my_mlx_put_pixel(double x, double y, int color, t_cub3D *cub)
{
	if ((x < 0 || x >= cub->screen_height) && (y < 0 || y >= cub->screen_width))
			return ;
	mlx_put_pixel(cub->__img, x, y, color);
}

void	find_horizontal_intersections(t_cub3D *map, double angle, t_vect *check)
{
	t_vect	step;
	t_vect	intersx;
	t_vect	next_touch;

	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	intersx.y = floor(map->player->pos.y / TILE_SIZE) * TILE_SIZE;
	if (angle > 0 && angle < M_PI)
		intersx.y += TILE_SIZE;
	intersx.x = map->player->pos.x + (intersx.y - map->player->pos.y) / tan(angle);
	step.y = TILE_SIZE;
	if (!(angle > 0 && angle < M_PI))
		step.y *= -1;
	step.x = TILE_SIZE / tan(angle);
	if (step.x > 0 && (angle > (M_PI / 2) && angle < (1.5 * M_PI)))
		step.x *= -1;
	if (step.x < 0 && !(angle > (M_PI / 2) && angle < (1.5 * M_PI)))
		step.x *= -1;
	next_touch = intersx;
	while (next_touch.x >= 0 && next_touch.x < map->screen_width \
		&& next_touch.y >= 0 && next_touch.y < map->screen_height)
	{
		check->x = next_touch.x;
		check->y = next_touch.y;
		if (!(angle > 0 && angle < M_PI))
			check->y--;
		map->hit_content_h = map->map->map[(int)check->y / TILE_SIZE][(int)check->x / TILE_SIZE];
		if (wall(map , check->x, check->y))
			break;
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	check->x = next_touch.x;
	check->y = next_touch.y;
}

void	find_vertical_intersections(t_cub3D *cub, double angle, t_vect *check)
{
	t_vect	step;
	t_vect	intersx;
	t_vect	next_touch;

	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	intersx.x = floor(cub->player->pos.x / TILE_SIZE) * TILE_SIZE;
	if (angle < M_PI / 2 || angle > M_PI * 1.5)
		intersx.x += TILE_SIZE;
	intersx.y = cub->player->pos.y + (intersx.x - cub->player->pos.x) * tan(angle);
	step.x = TILE_SIZE;
	if (angle > M_PI / 2 && angle < M_PI * 1.5)
		step.x *= -1;
	step.y = TILE_SIZE * tan(angle);
	if (step.y > 0 && !(angle > 0 && angle < M_PI))
		step.y *= -1;
	if (step.y < 0 && (angle > 0 && angle < M_PI))
		step.y *= -1;
	next_touch = intersx;
	while (next_touch.x >= 0 && next_touch.x < cub->screen_width \
		&& next_touch.y >= 0 && next_touch.y < cub->screen_height)
	{
		check->x = next_touch.x;
		check->y = next_touch.y;
		if ((angle > M_PI / 2 && angle < M_PI * 1.5))
			check->x--;
		cub->hit_content_v = cub->map->map[(int)check->y / TILE_SIZE][(int)check->x / TILE_SIZE];
		if (wall(cub , check->x, check->y))
			break;
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	check->x = next_touch.x;
	check->y = next_touch.y;
}

void    mini_map(t_cub3D *cub)
{
    int			x;
    int			y;

    y = 0;
    while (y < cub->screen_height / 5)
    {
            x = 0;
            while (x < cub->screen_width / 5)
            {
				if (remainder(x * 5, TILE_SIZE) == 0 || remainder(y * 5, TILE_SIZE) == 0)
					my_mlx_put_pixel(x, y, BLACK, cub);
                else if (cub->map->map[(int)(y * 5 / TILE_SIZE)][(int)(x * 5 / TILE_SIZE)] == 1)
                    my_mlx_put_pixel(x, y, ORANGE, cub);
				else if (cub->map->map[(int)(y * 5 / TILE_SIZE)][(int)(x * 5 / TILE_SIZE)] == 3)
					my_mlx_put_pixel(x, y, RED, cub);
				else if (cub->map->map[(int)(y * 5 / TILE_SIZE)][(int)(x * 5 / TILE_SIZE)] == 4)
					my_mlx_put_pixel(x, y, 0x00ff00ff, cub);
                else
                    my_mlx_put_pixel(x, y, BLACK, cub);
                x++;
            }
            y++;
    }
	x = -1;
	while (++x < SCREEN_WIDTH)
		bresenhams(cub->player->pos.x / 5, cub->player->pos.y / 5, cub->rays[x].wall_hit.x / 5 , cub->rays[x].wall_hit.y / 5, cub, WHITE);
}
