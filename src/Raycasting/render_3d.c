/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:06 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/02 13:22:57 by hbettal          ###   ########.fr       */
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
		cub->rays[x].hit_ver = false;
	}
	else
	{
		cub->rays[x].distance = v_distance;
		cub->rays[x].wall_hit = vcheck;
		cub->rays[x].hit_ver = true;
	}
}

int		get_color(t_map_info *map, char c)
{
	if (c == 'c')
	{
		return ((map->ceiling_color[0] << 24) + \
		(map->ceiling_color[1] << 16) + (map->ceiling_color[2] << 8) + 255);
	}
	return ((map->floor_color[0] << 24) + \
	(map->floor_color[1] << 16) + (map->floor_color[2] << 8) + 255);
}

void	draw_wall(int x, t_cub3D *cub)
{
	double	plane_distance;
	double	distance;
	double	wall_height;
	int		from_y;
	int		to_y;
	
	distance = cub->rays[x].distance * cos(cub->player->angle - cub->rays[x].rayAngle);
	plane_distance = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
	wall_height = (TILE_SIZE / distance) * plane_distance;
	from_y = SCREEN_HEIGHT / 2 - (int)wall_height / 2;
	to_y = SCREEN_HEIGHT / 2 + (int)wall_height / 2;
	if (from_y < 0)
		from_y = 0;
	if (to_y >= SCREEN_HEIGHT)
		to_y = SCREEN_HEIGHT; 
	if (cub->rays[x].hit_ver)
		bresenhams(x, from_y, x, to_y, cub, 0xCCCCCCFF);
	else
		bresenhams(x, from_y, x, to_y, cub, WHITE);
	bresenhams(x, 0, x, from_y, cub, get_color(cub->map->map_info, 'c'));
	bresenhams(x, to_y, x, SCREEN_HEIGHT, cub, get_color(cub->map->map_info, 'f'));
}

void    render_3d(t_cub3D *cub)
{
	int			x;
	double		rays;
	t_vect		vcheck;
	t_vect		hcheck;
	
	cub->__img = mlx_new_image(cub->__mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!cub->__img)
    {
            printf("%s\n", mlx_strerror(MLX_INVIMG));
            exit(1);
    }
    mlx_image_to_window(cub->__mlx, cub->__img, 0, 0);
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
	mini_map(cub);
}