/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:56:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/30 16:23:07 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void    my_mlx_put_pixel(double x, double y, int color, t_cub3D *cub)
{
        if ((x < 0 || x >= cub->screen_height) && (y < 0 || y >= cub->screen_width))
                return ;
        mlx_put_pixel(cub->__img, x, y, color);
}

void	find_horizontal_intersections(t_cub3D *map, double angle, t_vect *check, int x)
{
	t_vect	step;
	t_vect	intersx;
	t_vect	next_touch;
	(void)x;
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
		if (wall(map , check->x, check->y))
		{

			break;
		}
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	check->x = next_touch.x;
	check->y = next_touch.y;
	// map->rays[x].wall_content = map->map->map[(int)floor(check->y / TILE_SIZE)]\
	// [(int)floor(check->x / TILE_SIZE)];
}
void	find_vertical_intersections(t_cub3D *cub, double angle, t_vect *check, int x)
{
	t_vect	step;
	t_vect	intersx;
	t_vect	next_touch;

	(void)x;
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
		if (wall(cub, check->x, check->y))
			break;
		next_touch.x += step.x;
		next_touch.y += step.y;
	}
	check->x = next_touch.x;
	check->y = next_touch.y;
	// cub->rays[x].wall_content = cub->map->map[(int)floor(check->y / TILE_SIZE)]\
	// [(int)floor(check->x / TILE_SIZE)];
}

void    calcule_close_ray(t_cub3D *cub, t_vect vcheck, t_vect hcheck, int x)
{
    double     v_distance;
    double     h_distance;

    h_distance = sqrt(pow(hcheck.x - cub->player->pos.x, 2) + pow(hcheck.y - cub->player->pos.y, 2));
    v_distance = sqrt(pow(vcheck.x - cub->player->pos.x, 2) + pow(vcheck.y  - cub->player->pos.y, 2));
    if (v_distance > h_distance)
	{
        // bresenhams(cub->player->pos.x, cub->player->pos.y, cub->h_ray->x, cub->h_ray->y, cub, WHITE);
		cub->rays[x].distance = h_distance;
		cub->rays[x].wall_hit = hcheck;
	}
	else
	{
		cub->rays[x].distance = v_distance;
		cub->rays[x].wall_hit = vcheck;
	}
        // bresenhams(cub->player->pos.x, cub->player->pos.y, cub->v_ray->x, cub->v_ray->y, cub, WHITE);
}

// void	draw_wall(int x, int distance, t_cub3D *cub, double rays)
// {
// 	int calcule;
// 	int distance_rem;
// 	int from_y;
// 	int to_y;
// 	(void)rays;
	
// 	distance_rem = distance;
// 	calcule = cub->screen_height / 2;
// 	calcule = calcule / distance;
// 	from_y = cub->screen_height / 2 - calcule;
// 	from_y = from_y / 2;
// 	to_y = from_y + calcule;
// 	// printf("-------------->> (%d)\n", calcule);
// 	bresenhams(x, from_y / 1.5, x, to_y * 1.5, cub, WHITE);
// }

void    render_2d(t_cub3D *cub)
{
    int			x;
    double			y;
    double			rays;
	t_vect	vcheck;
	t_vect	hcheck;

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
		if (remainder(x, TILE_SIZE) == 0 || remainder(y, TILE_SIZE) == 0)
			my_mlx_put_pixel(x, y, BLACK, cub);
                    else if (cub->map->map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] == 1)
                            my_mlx_put_pixel(x, y, ORANGE, cub);
                    else
                            my_mlx_put_pixel(x, y, BLACK, cub);
                    x++;
            }
            y++;
    }
    rays = cub->player->angle - (FOV_ANGLE / 2);
	x = -1;
	while (++x < cub->screen_width)
	{
		printf("x = %d\n", x);
		find_vertical_intersections(cub, rays, &vcheck, x);
		find_horizontal_intersections(cub, rays, &hcheck, x);	
        calcule_close_ray(cub, vcheck, hcheck, x);
        rays += FOV_ANGLE / cub->screen_width;
	}
	for (int i = 0; i < cub->screen_width; i++)
	{
		bresenhams(cub->player->pos.x, cub->player->pos.y, cub->rays[i].wall_hit.x, cub->rays[i].wall_hit.y, cub, WHITE);
	}
}
