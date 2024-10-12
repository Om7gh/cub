/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:06 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/12 20:05:17 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void calcule_close_ray(t_cub3D *cub, t_vect vcheck, t_vect hcheck, int x)
{
    double v_distance;
    double h_distance;

    h_distance = sqrt(pow(hcheck.x - cub->player->pos.x, 2) + pow(hcheck.y - cub->player->pos.y, 2));
    v_distance = sqrt(pow(vcheck.x - cub->player->pos.x, 2) + pow(vcheck.y  - cub->player->pos.y, 2));
    if (v_distance > h_distance)
    {
        cub->rays[x].wall_content = cub->hit_content_h;
        cub->rays[x].distance = h_distance;
        cub->rays[x].wall_hit = hcheck;
        cub->rays[x].hit_ver = false;
    }
    else
    {
        cub->rays[x].wall_content = cub->hit_content_v;
        cub->rays[x].distance = v_distance;
        cub->rays[x].wall_hit = vcheck;
        cub->rays[x].hit_ver = true;
    }
}

int get_color(t_map_info *map, char c, t_cub3D *cub, int x)
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

void apply_shadow(uint32_t *color, double distance, double max_distance)
{
    double intensity = 1.1 - (distance / max_distance);

    if (intensity < 0.3)
        intensity = 0.3;
    uint32_t r = (*color >> 24) & 0xFF;
    uint32_t g = (*color >> 16) & 0xFF;
    uint32_t b = (*color >> 8) & 0xFF;
    r *= intensity;
    g *= intensity;
    b *= intensity;
    *color = (r << 24) | (g << 16) | (b << 8) | 150;
}

uint32_t get_texture_pixel(mlx_image_t *texture, int x, int y)
{
    uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	int		index;

	if (x >= 0 && (uint32_t)x < texture->width
		&& y >= 0 && (uint32_t)y < texture->height)
	{
		index = (y * texture->width + x) * 4;
		r = texture->pixels[index];
		g = texture->pixels[index + 1];
		b = texture->pixels[index + 2];
		a = texture->pixels[index + 3];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0x000000FF);
}

void draw_wall(int x, t_cub3D *cub)
{
    double plane_distance;
    double distance;
    double wall_height;
    t_vect from;
    t_vect to;
    int tmp;

    distance = cub->rays[x].distance * cos(cub->player->angle - cub->rays[x].rayAngle);
    double max_distance = 300;
    plane_distance = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
    wall_height = (T_L / distance) * plane_distance;
    from.y = SCREEN_HEIGHT / 2 - (int)wall_height / 2;
    to.y = SCREEN_HEIGHT / 2 + (int)wall_height / 2;
    to.x = x;
    from.x = x;
    if (from.y < 0)
        from.y = 0;
    if (to.y >= SCREEN_HEIGHT)
        to.y = SCREEN_HEIGHT;
    double wall_x;
    wall_x = 0;
    if (cub->rays[x].hit_ver)
        wall_x = cub->rays[x].wall_hit.y / T_L;
    else
        wall_x = cub->rays[x].wall_hit.x / T_L;
    wall_x -= floor(wall_x);
    int tex_width = cub->texture_img_no->width;
    int tex_height = cub->texture_img_no->height;
    int texture_x = (int)(wall_x * tex_width) % tex_width;
    double step = (double)tex_height / wall_height;
    double texture_pos = (from.y - (SCREEN_HEIGHT / 2 - wall_height / 2)) * step;
    mlx_image_t *current_texture;
    current_texture = cub->texture_img_no; 
    if (cub->rays[x].wall_content == 1)
        current_texture = cub->texture_img_no;
    uint32_t color;
    for (int y = from.y; y < to.y; y++)
    {
        int texture_y = (int)texture_pos % tex_height;
        texture_pos += step;
        if (cub->rays[x].wall_content == 1)
            current_texture = cub->texture_img_no;
        if (cub->rays[x].wall_content == 3)
            current_texture = cub->door_img;
        color = get_texture_pixel(current_texture, texture_x, texture_y);
        apply_shadow(&color, distance, max_distance);
        mlx_put_pixel(cub->__img, x, y, color);
    }
    tmp = to.y;
    to.y = 0;
    bresenhams(from, to, cub, get_color(cub->map->map_info, 'c', cub, x));
    to.y = tmp;
    from.y = SCREEN_HEIGHT;
    bresenhams(from, to, cub, get_color(cub->map->map_info, 'f', cub, x));
}

void render_3d(t_cub3D *cub)
{
    int x;
    double rays;
    t_vect vcheck;
    t_vect hcheck;

    rays = cub->player->angle - (FOV_ANGLE / 2);
    x = -1;
    while (++x < SCREEN_WIDTH)
    {
        rays = remainder(rays, 2 * M_PI);
        if (rays < 0)
            rays += 2 * M_PI;
        cub->rays[x].rayAngle = rays;
        find_horizontal_intersx(cub, rays, &hcheck);
        find_vertical_intersx(cub, rays, &vcheck);
        calcule_close_ray(cub, vcheck, hcheck, x);
        draw_wall(x, cub);
        rays += FOV_ANGLE / SCREEN_WIDTH;
    }
    mini_map(cub);
}
