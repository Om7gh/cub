/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:56:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/14 18:58:40 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    my_mlx_put_pixel(unsigned int x, unsigned int y, int color, t_cub3D *cub)
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
	intersx.x = map->player->pos.x + (intersx.y - map->player->pos.y) / tan(angle);
	step.y = TILE_SIZE;
	if (!(angle > 0 && angle < M_PI))
		step.y *= -1;
	step.x = TILE_SIZE / tan(angle);
	if (step.x > 0 && (angle > (M_PI / 2) && angle < (1.5 * M_PI)))
		step.x *= -1;
	if (step.x < 0 && !(angle > (M_PI / 2) && angle < (1.5 * M_PI)))
		step.x *= -1;
	next_touch.x = intersx.x;
	next_touch.y = intersx.y;
	while (next_touch.x >= 0 && next_touch.x < map->screen_width \
		&& next_touch.y >= 0 && next_touch.y < map->screen_height)
	{
		check->x = next_touch.x;
		check->y = next_touch.y;
		if (!(angle > 0 && angle < M_PI))
			check->y--;
		if (wall(map , check->x, check->y))
			break;
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
}

void	find_vertical_intersections(t_cub3D *map, double angle, t_vect *check)
{
	t_vect	step;
	t_vect	intersx;
	t_vect	next_touch;

	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	intersx.x = floor(map->player->pos.x / TILE_SIZE) * TILE_SIZE;
	intersx.y = map->player->pos.y + (intersx.x - map->player->pos.x) * tan(angle);
	step.x = TILE_SIZE;
	if (angle > M_PI / 2 && angle < M_PI * 1.5)
		step.x *= -1;
	step.y = TILE_SIZE * tan(angle);
	if (step.y > 0 && !(angle > 0 && angle < M_PI))
		step.y *= -1;
	if (step.y < 0 && (angle > 0 && angle < M_PI))
		step.y *= -1;
	next_touch.x = intersx.x;
	next_touch.y = intersx.y;
	while (next_touch.x >= 0 && next_touch.x < map->screen_width \
		&& next_touch.y >= 0 && next_touch.y < map->screen_height)
	{
		check->x = next_touch.x;
		check->y = next_touch.y;
		if ((angle > M_PI / 2 && angle < M_PI * 1.5))
			check->x--;
		if (wall(map, check->x, check->y))
			break;
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
}

void    calcule_close_ray(t_cub3D *cub)
{
        double     v_distance;
        double     h_distance;

        h_distance = sqrt(pow(cub->h_ray->x - cub->player->pos.x, 2) + pow(cub->h_ray->y - cub->player->pos.y, 2));
        v_distance = sqrt(pow(cub->v_ray->x - cub->player->pos.x, 2) + pow(cub->v_ray->y  - cub->player->pos.x, 2));
        if (v_distance > h_distance)
        {
                cub->v_ray->x = cub->h_ray->x;
                cub->v_ray->y = cub->h_ray->y;
        }
}

void    render_2d(t_cub3D *cub)
{
        unsigned int     x;
        unsigned int     y;
        double rays;
	t_vect	check1 ;
	t_vect	check2 ;

        y = 0;
         cub->__img = mlx_new_image(cub->__mlx, cub->screen_width, cub->screen_height);
        if (!cub->__img)
        {
                printf("%s\n", mlx_strerror(MLX_INVIMG));
                exit(1);
        }
        mlx_image_to_window(cub->__mlx, cub->__img, 0, 0);
        while (y < cub->screen_height)
        {
                x = 0;
                while (x < cub->screen_width)
                {
                        if (cub->map->map[y / TILE_SIZE][x / TILE_SIZE] == 1)
                                my_mlx_put_pixel(x, y, ORANGE, cub);
                        else
                                my_mlx_put_pixel(x, y, BLACK, cub);
                        x++;
                }
                y++;
        }
        rays = -0.45;
        while (rays < 0.45)
        {
                find_vertical_intersections(cub, cub->player->angle + rays, &check1);
		cub->v_ray = &check1;
                find_horizontal_intersections(cub, cub->player->angle + rays, &check2);
		cub->h_ray = &check2;
                calcule_close_ray(cub);
                // printf("x = %f || y = %f\n", cub->v_ray->x, cub->v_ray->y);
                bresenhams(cub->player->pos.x, cub->player->pos.y, cub->v_ray->x, cub->v_ray->y, cub, WHITE);
                rays += 0.005;
        }
	printf("vh %p\t h %p\n", cub->v_ray, cub->h_ray);
}
