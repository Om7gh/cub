/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:06 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/13 18:48:10 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void calcule_close_ray(t_cub3d *cub, t_vect vcheck, t_vect hcheck, int x)
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

int get_color(t_map_info *map, char c, t_cub3d *cub, int x)
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
	double intensity = 1 - (distance / max_distance);

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

	if (!texture)
		return (0);
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
	return (0xFFFFFFFF);
}

void	draw_floor_ceil(t_vect from, t_vect to, t_cub3d *cub, int x)
{
	int	tmp;

	tmp = to.y;
	to.y = 0;
	bresenhams(from, to, cub, get_color(cub->map->map_info, 'c', cub, x));
	to.y = tmp;
	from.y = SCREEN_HEIGHT;
	bresenhams(from, to, cub, get_color(cub->map->map_info, 'f', cub, x));
}

void	wall_loop(t_vect from, t_vect to, t_cub3d *cub, int x)
{
	int	y;

	y = from.y;
	mlx_image_t *current_texture;
	current_texture = NULL; 
	while (y < to.y)
	{
		cub->texture_y = (int)cub->texture_pos % cub->tex_height;
		cub->texture_pos += cub->step;
		if (cub->rays[x].wall_content == 1)
		{
			if (cub->rays[x].hit_ver && cub->rays[x].rayangle <= 1.5 * M_PI && cub->rays[x].rayangle >= 0.5 * M_PI)
				current_texture = cub->texture_img_ea;
			else if (cub->rays[x].hit_ver && !(cub->rays[x].rayangle <= 1.5 * M_PI && cub->rays[x].rayangle >= 0.5 * M_PI))
				current_texture = cub->texture_img_we;
			else if (!cub->rays[x].hit_ver && (cub->rays[x].rayangle >= 0 && cub->rays[x].rayangle <= M_PI))
				current_texture = cub->texture_img_so;
			else if (!cub->rays[x].hit_ver && !(cub->rays[x].rayangle >= 0 && cub->rays[x].rayangle <= M_PI))
				current_texture = cub->texture_img_no;
		}
		if (cub->rays[x].wall_content == 3)
			current_texture = cub->door_img;
		cub->color = get_texture_pixel(current_texture, cub->texture_x, cub->texture_y);
		apply_shadow(&cub->color, cub->distance, 700);
		mlx_put_pixel(cub->__img, x, y, cub->color);
		y++;
	}
}

void	get_exact_pos(t_vect *from, t_vect *to, double wall_height, int x)
{
	(*from).y = SCREEN_HEIGHT / 2 - (int)wall_height / 2;
	(*to).y = SCREEN_HEIGHT / 2 + (int)wall_height / 2;
	(*to).x = x;
	(*from).x = x;
	if ((*from).y < 0)
		(*from).y = 0;
	if ((*to).y >= SCREEN_HEIGHT)
		(*to).y = SCREEN_HEIGHT;
}

void draw_wall(int x, t_cub3d *cub)
{
	double plane_distance;
	double wall_height;
	t_vect from;
	t_vect to;

	wall_height = 0.0;
	cub->distance = cub->rays[x].distance * cos(cub->player->angle - cub->rays[x].rayangle);
	plane_distance = (SCREEN_WIDTH / 2) / tan(cub->fov / 2);
	wall_height = (T_L / cub->distance) * plane_distance;
	get_exact_pos(&from, &to, wall_height, x);
	cub->wall_x = 0;
	if (cub->rays[x].hit_ver)
		cub->wall_x = cub->rays[x].wall_hit.y / T_L;
	else
		cub->wall_x = cub->rays[x].wall_hit.x / T_L;
	cub->wall_x -= floor(cub->wall_x);
	cub->tex_width = cub->texture_img_no->width;
	cub->tex_height = cub->texture_img_no->height;
	cub->texture_x = (int)(cub->wall_x * cub->tex_width) % cub->tex_width;
	cub->step = (double)cub->tex_height / wall_height;
	cub->texture_pos = (from.y - (SCREEN_HEIGHT / 2 - wall_height / 2)) * cub->step;
	wall_loop(from, to, cub, x);
	draw_floor_ceil(from, to, cub, x);
}

void render_3d(t_cub3d *cub)
{
	int x;
	double rays;
	t_vect vcheck;
	t_vect hcheck;

	rays = cub->player->angle - (cub->fov / 2);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		rays = remainder(rays, 2 * M_PI);
		if (rays < 0)
			rays += 2 * M_PI;
		cub->rays[x].rayangle = rays;
		find_horizontal_intersx(cub, rays, &hcheck);
		find_vertical_intersx(cub, rays, &vcheck);
		calcule_close_ray(cub, vcheck, hcheck, x);
		draw_wall(x, cub);
		rays += cub->fov / SCREEN_WIDTH;
	}
	mini_map(cub);
}
