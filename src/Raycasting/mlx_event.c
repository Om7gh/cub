/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:15:02 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/14 18:29:53 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_rays(t_cub3d *cub)
{
	int		x;
	t_vect	from;
	t_vect	to;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		from.x = cub->player->pos.x * cub->scale;
		from.y = cub->player->pos.y * cub->scale;
		to.x = cub->rays[x].wall_hit.x * cub->scale;
		to.y = cub->rays[x].wall_hit.y * cub->scale;
		bresenhams(from, to, cub, WHITE);
	}
}

int	wall(t_cub3d *cub, double x, double y)
{
	t_door	*door;

	if (x < 0 || x > cub->screen_width || y < 0 || y > cub->screen_height)
		return (1);
	if (cub->map->map[(int)y / T_L][(int)x / T_L] == 1)
		return (1);
	if (cub->map->map[(int)floor(y / T_L)][(int)floor(x / T_L)] == 3)
	{
		door = get_door(&cub->doors, x, y);
		if (!door)
			return (1);
		if (door->is_facingx && door->y * T_L > y + (T_L * door->progress) / 2 \
		&& door->y * T_L - T_L / 2 <= y + (T_L * (1 - door->progress)) / 2)
			return (0);
		if (!door->is_facingx && door->x * T_L >= x + (T_L * door->progress) \
		/ 2 && door->x * T_L - T_L / 2 < x + (T_L * (1 - door->progress)) / 2)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	arrow_handler(mlx_key_data_t key, t_cub3d *cub)
{
	if (key.key == MLX_KEY_W)
		cub->player->walk_direction = 1;
	else if (key.key == MLX_KEY_S)
		cub->player->walk_direction = -1;
	else if (key.key == MLX_KEY_A)
		cub->player->arrow = -1;
	else if (key.key == MLX_KEY_D)
		cub->player->arrow = 1;
	else if (key.key == MLX_KEY_LEFT)
		cub->player->turn_direction = -1;
	else if (key.key == MLX_KEY_RIGHT)
		cub->player->turn_direction = 1;
	if (key.action == MLX_RELEASE)
	{
		if (key.key == MLX_KEY_W || key.key == MLX_KEY_S)
			cub->player->walk_direction = 0;
		else if (key.key == MLX_KEY_A || key.key == MLX_KEY_D)
			cub->player->arrow = 0;
		else if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
			cub->player->turn_direction = 0;
	}
}

void	key_handler(mlx_key_data_t key, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (key.action != MLX_RELEASE)
	{
		if (key.key == 320)
			cub->cursor_hidden = 1;
		if (key.key == 321)
			cub->cursor_hidden = 0;
		if (key.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(cub->__mlx);
			mlx_terminate(cub->__mlx);
			exit(0);
		}
		if (key.key >= 0 && key.key <= 320)
		{
			cub->intro_img = cub->__img;
		}
		if (key.key == MLX_KEY_SPACE)
			open_door(cub);
	}
	arrow_handler(key, cub);
}

void	mouse_handler(double xpos, double ypos, void *param)
{
	t_cub3d	*cub;

	(void)ypos;
	cub = (t_cub3d *)param;
	mlx_set_cursor_mode(cub->__mlx, MLX_MOUSE_HIDDEN);
	if (cub->cursor_hidden && cub->player->prev_x > xpos)
		cub->player->angle -= fabs(cub->player->prev_x - xpos) * 0.004;
	else if (cub->cursor_hidden && cub->player->prev_x < xpos)
		cub->player->angle += fabs(cub->player->prev_x - xpos) * 0.004;
	cub->player->prev_x = xpos;
}
