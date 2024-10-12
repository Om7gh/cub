/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:56:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 13:27:17 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	my_mlx_put_pixel(double x, double y, int color, t_cub3D *cub)
{
	if ((x < 0 || x >= cub->screen_height) && (y < 0 || y >= cub->screen_width))
		return ;
	mlx_put_pixel(cub->__img, x, y, color);
}

t_vect	first_horizontal_touch(t_cub3D *cub, double angle, t_vect *step)
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

void	find_horizontal_intersx(t_cub3D *cub, double angle, t_vect *check)
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

t_vect	first_vertical_touch(t_cub3D *cub, double angle, t_vect *step)
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

void	find_vertical_intersx(t_cub3D *cub, double angle, t_vect *check)
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

void	mini_map(t_cub3D *cub)
{
	t_vect	from;
	t_vect	to;
	int		x;

	from.y = -1;
	while (++from.y < cub->screen_height / 6)
	{
		from.x = -1;
		while (++from.x < cub->screen_width / 6)
		{
			if (cub->map->map[(int)(from.y * 6 / T_L)][(int)(from.x * 6 / T_L)] == 1)
				my_mlx_put_pixel(from.x, from.y, ORANGE, cub);
			else if (cub->map->map[(int)(from.y * 6 / T_L)][(int)(from.x * 6 / T_L)] == 3)
				my_mlx_put_pixel(from.x, from.y, RED, cub);
			else
				my_mlx_put_pixel(from.x, from.y, BLACK, cub);
		}
	}
	x = -1;
	1 && (from.x = cub->player->pos.x / 6), (from.y = cub->player->pos.y / 6);
	while (++x < SCREEN_WIDTH)
	{
		1 && (to.x = cub->rays[x].wall_hit.x / 6), (to.y = cub->rays[x].wall_hit.y / 6);
		bresenhams(from, to, cub, WHITE);
	}
}
