/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:06 by hbettal           #+#    #+#             */
/*   Updated: 2024/09/30 21:58:34 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    calcule_close_ray(t_cub3D *cub, t_vect vcheck, t_vect hcheck, int x)
{
    double     v_distance;
    double     h_distance;

    h_distance = sqrt(pow(hcheck.x - cub->player->pos.x, 2) + pow(hcheck.y - cub->player->pos.y, 2));
    v_distance = sqrt(pow(vcheck.x - cub->player->pos.x, 2) + pow(vcheck.y  - cub->player->pos.y, 2));
    if (v_distance > h_distance)
	{
		cub->rays[x].distance = h_distance;
		cub->rays[x].wall_hit = hcheck;
		cub->rays->hit_ver = false;
	}
	else
	{
		cub->rays[x].distance = v_distance;
		cub->rays[x].wall_hit = vcheck;
		cub->rays->hit_ver = true;
	}
}

void	draw_wall(int x, t_cub3D *cub)
{
	double	distance_plane;
	double	distance_rem;
	double	wall_height;
	int		from_y;
	int		to_y;
	
	distance_rem = cub->rays[x].distance * cos(cub->rays[x].rayAngle - cub->player->angle);
	distance_plane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	wall_height = (TILE_SIZE / distance_rem) * distance_plane;
	from_y = SCREEN_HEIGHT / 2 - (int)wall_height / 2;
	to_y = SCREEN_HEIGHT / 2 + (int)wall_height / 2;
	if (from_y < 0)
		from_y = 0;
	if (to_y >= SCREEN_HEIGHT)
		to_y = SCREEN_HEIGHT;
	printf("from_y = %d, to_y = %d\n", from_y, to_y);
	printf("screen_height = %d || wall_height = %d\n", SCREEN_HEIGHT, SCREEN_WIDTH);
	bresenhams(x, from_y, x, to_y, cub, WHITE);
}

void    render_3d(t_cub3D *cub)
{
	int			x;
	double		rays;
	t_vect		vcheck;
	t_vect		hcheck;
	
	rays = cub->player->angle - (FOV_ANGLE / 2);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		cub->rays[x].rayAngle = rays;
		find_vertical_intersections(cub, rays, &vcheck, x);
		find_horizontal_intersections(cub, rays, &hcheck, x);
		calcule_close_ray(cub, vcheck, hcheck, x);
		draw_wall(x, cub);
		rays += FOV_ANGLE / SCREEN_WIDTH;
	}
}