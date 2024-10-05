/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:06 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/05 11:36:04 by omghazi          ###   ########.fr       */
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
	// printf("horizontal %f\n", h_distance);
	// printf("vertical %f\n", v_distance);
}

int	get_color(t_map_info *map, char c, t_cub3D *cub, int x)
{
	(void)x;
	(void)cub;
	if (c == 'c')
	{
		return ((map->ceiling_color[0] << 24) + \
		(map->ceiling_color[1] << 16) + (map->ceiling_color[2] << 8) + 255);
	}
	return ((map->floor_color[0] << 24) + \
	(map->floor_color[1] << 16) + (map->floor_color[2] << 8) + 255);
}

void    apply_shadow(uint32_t *color, double distance, double max_distance)
{
    double intensity = 1 - (distance / max_distance);
    if (intensity < 0.3)
        intensity = 0.3;
    
    uint32_t r = (*color >> 24) & 0xFF;
    uint32_t g = (*color >> 16) & 0xFF;
    uint32_t b = (*color >> 8) & 0xFF;
    r *= intensity;
    g *= intensity;
    b *= intensity;
    *color = (r << 24) | (g << 16) | (b << 8) | 0xff;
}

void    draw_wall(int x, t_cub3D *cub)
{
    double  plane_distance;
    double  distance;
    double  wall_height;
    int     from_y;
    int     to_y;
    uint32_t color = 0xffffffff;

    distance = cub->rays[x].distance * cos(cub->player->angle - cub->rays[x].rayAngle);
    double max_distance = 600;
    plane_distance = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
    wall_height = (TILE_SIZE / distance) * plane_distance;
    from_y = SCREEN_HEIGHT / 2 - (int)wall_height / 2;
    to_y = SCREEN_HEIGHT / 2 + (int)wall_height / 2;
    if (from_y < 0)
        from_y = 0;
    if (to_y >= SCREEN_HEIGHT)
        to_y = SCREEN_HEIGHT;
    apply_shadow(&color, distance, max_distance);
	if (cub->rays[x].wall_content == 3)
		bresenhams(x, from_y, x, to_y, cub, 0xC0FAF9FF);
	else
    	bresenhams(x, from_y, x, to_y, cub, color);
    bresenhams(x, 0, x, from_y, cub, get_color(cub->map->map_info, 'c', cub, x));
    bresenhams(x, to_y, x, SCREEN_HEIGHT, cub, get_color(cub->map->map_info, 'f', cub, x));
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
	mini_map(cub);
}
