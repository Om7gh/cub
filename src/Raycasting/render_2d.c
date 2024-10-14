/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:56:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/14 22:50:00 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vect	first_horizontal_touch(t_cub3d *cub, double angle, t_vect *step)
{
	t_vect	intersx;

	intersx.y = floor(cub->player->pos.y / T_L) * T_L;
	if (angle > 0 && angle < M_PI)
		intersx.y += T_L;
	intersx.x = cub->player->pos.x + \
	(intersx.y - cub->player->pos.y) / tan(angle);
	step->y = T_L;
	if (!(angle > 0 && angle < M_PI))
		step->y *= -1;
	step->x = T_L / tan(angle);
	if (step->x > 0 && (angle > (M_PI / 2) && angle < (1.5 * M_PI)))
		step->x *= -1;
	if (step->x < 0 && !(angle > (M_PI / 2) && angle < (1.5 * M_PI)))
		step->x *= -1;
	return (intersx);
}

void	find_horizontal_intersx(t_cub3d *cub, double angle, t_vect *check)
{
	t_vect	step;
	t_vect	next_touch;

	next_touch = first_horizontal_touch(cub, angle, &step);
	while (next_touch.x >= 0 && next_touch.x < cub->screen_width \
		&& next_touch.y >= 0 && next_touch.y < cub->screen_height)
	{
		check->x = next_touch.x;
		check->y = next_touch.y;
		if (!(angle > 0 && angle < M_PI))
			check->y--;
		cub->hit_content_h = \
		cub->map->map[(int)check->y / T_L][(int)check->x / T_L];
		if (wall(cub, check->x, check->y))
			break ;
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	check->x = next_touch.x;
	check->y = next_touch.y;
}

t_vect	first_vertical_touch(t_cub3d *cub, double angle, t_vect *step)
{
	t_vect	intersx;

	intersx.x = floor(cub->player->pos.x / T_L) * T_L;
	if (angle < M_PI / 2 || angle > M_PI * 1.5)
		intersx.x += T_L;
	intersx.y = cub->player->pos.y + \
	(intersx.x - cub->player->pos.x) * tan(angle);
	step->x = T_L;
	if (angle > M_PI / 2 && angle < M_PI * 1.5)
		step->x *= -1;
	step->y = T_L * tan(angle);
	if (step->y > 0 && !(angle > 0 && angle < M_PI))
		step->y *= -1;
	if (step->y < 0 && (angle > 0 && angle < M_PI))
		step->y *= -1;
	return (intersx);
}

void	find_vertical_intersx(t_cub3d *cub, double angle, t_vect *check)
{
	t_vect	next_touch;
	t_vect	step;

	next_touch = first_vertical_touch(cub, angle, &step);
	while (next_touch.x >= 0 && next_touch.x < cub->screen_width \
		&& next_touch.y >= 0 && next_touch.y < cub->screen_height)
	{
		check->x = next_touch.x;
		check->y = next_touch.y;
		if ((angle > M_PI / 2 && angle < M_PI * 1.5))
			check->x--;
		cub->hit_content_v = \
		cub->map->map[(int)check->y / T_L][(int)check->x / T_L];
		if (wall(cub, check->x, check->y))
			break ;
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	check->x = next_touch.x;
	check->y = next_touch.y;
}

void	mini_map(t_cub3d *cub)
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
	draw_rays(cub);
}
