/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:13:46 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/24 15:26:23 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_color(t_map_info *map, char c)
{
	if (c == 'c')
	{
		return ((map->ceiling_color[0] << 24) + \
		(map->ceiling_color[1] << 16) + (map->ceiling_color[2] << 8) + 255);
	}
	return ((map->floor_color[0] << 24) + \
	(map->floor_color[1] << 16) + (map->floor_color[2] << 8) + 255);
}

void	apply_shadow(uint32_t *color, double distance, double max_distance)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	double		intensity;

	intensity = 1 - (distance / max_distance);
	if (intensity < 0.3)
		intensity = 0.3;
	r = (*color >> 24) & 0xFF;
	g = (*color >> 16) & 0xFF;
	b = (*color >> 8) & 0xFF;
	r *= intensity;
	g *= intensity;
	b *= intensity;
	*color = (r << 24) | (g << 16) | (b << 8) | 0xff;
}

uint32_t	get_texture_pixel(mlx_image_t *texture, int x, int y)
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

void	draw_floor_ceil(t_vect from, t_vect to, t_cub3d *cub)
{
	int	tmp;

	tmp = to.y;
	to.y = 0;
	bresenhams(from, to, cub, get_color(cub->map->map_info, 'c'));
	to.y = tmp;
	from.y = SCREEN_HEIGHT;
	bresenhams(from, to, cub, get_color(cub->map->map_info, 'f'));
}

void	check_texture_angle(t_cub3d *cub, int x, mlx_image_t **current_texture)
{
	if (cub->rays[x].hit_ver && cub->rays[x].rayangle <= 1.5 * M_PI \
		&& cub->rays[x].rayangle >= 0.5 * M_PI)
		*current_texture = cub->texture_img_ea;
	else if (cub->rays[x].hit_ver && !(cub->rays[x].rayangle <= 1.5 \
		* M_PI && cub->rays[x].rayangle >= 0.5 * M_PI))
		*current_texture = cub->texture_img_we;
	else if (!cub->rays[x].hit_ver && (cub->rays[x].rayangle >= 0 \
		&& cub->rays[x].rayangle <= M_PI))
		*current_texture = cub->texture_img_so;
	else if (!cub->rays[x].hit_ver && !(cub->rays[x].rayangle >= 0 \
		&& cub->rays[x].rayangle <= M_PI))
		*current_texture = cub->texture_img_no;
}
