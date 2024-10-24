/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:50:06 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/24 15:21:11 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calcule_close_ray(t_cub3d *cub, t_vect vcheck, t_vect hcheck, int x)
{
	double	v_distance;
	double	h_distance;

	h_distance = sqrt(pow(hcheck.x - cub->player->pos.x, 2) \
		+ pow(hcheck.y - cub->player->pos.y, 2));
	v_distance = sqrt(pow(vcheck.x - cub->player->pos.x, 2) \
		+ pow(vcheck.y - cub->player->pos.y, 2));
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

void	wall_loop(t_vect from, t_vect to, t_cub3d *cub, int x)
{
	mlx_image_t	*current_texture;
	int			y;

	y = from.y;
	while (y < to.y)
	{
		cub->texture_y = (int)cub->texture_pos % cub->tex_height;
		cub->texture_pos += cub->step;
		if (cub->rays[x].wall_content == 1)
			check_texture_angle(cub, x, &current_texture);
		if (cub->rays[x].wall_content == 3)
			current_texture = cub->door_img;
		cub->color = get_texture_pixel(current_texture, \
			cub->texture_x, cub->texture_y);
		apply_shadow(&cub->color, cub->distance, 900);
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

void	draw_wall(int x, t_cub3d *cub)
{
	t_vect	to;
	t_vect	from;
	double	plane_distance;
	double	wall_height;

	wall_height = 0.0;
	cub->distance = cub->rays[x].distance * cos(cub->player->angle \
		- cub->rays[x].rayangle);
	plane_distance = (SCREEN_WIDTH / 2) / tan(cub->fov / 2);
	wall_height = (T_L / cub->distance) * plane_distance;
	get_exact_pos(&from, &to, wall_height, x);
	cub->wall_x = 0;
	if (cub->rays[x].hit_ver)
		cub->wall_x = cub->rays[x].wall_hit.y / T_L;
	else
		cub->wall_x = cub->rays[x].wall_hit.x / T_L;
	cub->wall_x -= floor(cub->wall_x);
	cub->tex_width = get_texture_width(cub, x);
	cub->tex_height = get_texture_height(cub, x);
	cub->texture_x = (int)(cub->wall_x * cub->tex_width) % cub->tex_width;
	cub->step = (double)cub->tex_height / wall_height;
	cub->texture_pos = (from.y - (SCREEN_HEIGHT / 2 - wall_height / 2)) \
		* cub->step;
	wall_loop(from, to, cub, x);
	draw_floor_ceil(from, to, cub);
}

void	render_3d(t_cub3d *cub)
{
	t_vect	vcheck;
	t_vect	hcheck;
	double	rays;
	int		x;

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
