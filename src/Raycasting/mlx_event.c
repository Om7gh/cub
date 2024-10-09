/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:15:02 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/09 09:22:13 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_door	*get_door(t_door **door, double x, double y)
{
	t_door	*tmp;

	if (!door)
		return (NULL);
	tmp = *door;
	while (tmp)
	{
		if (tmp->x * TILE_SIZE - TILE_SIZE <= x && tmp->x * TILE_SIZE + TILE_SIZE >= x && tmp->y * TILE_SIZE - TILE_SIZE <= y && tmp->y * TILE_SIZE + TILE_SIZE >= y)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int     wall(t_cub3D *cub, double x, double y)
{
	int		x_distace;
	int		y_distace;
	t_door	*door;

	if (x < 0 || x > cub->screen_width || y < 0 || y > cub->screen_height)
		return (1);
	if (cub->map->map[(int)floor(y / TILE_SIZE)][(int)floor(x / TILE_SIZE)] == 1)
		return (1);
	if (cub->map->map[(int)floor(y / TILE_SIZE)][(int)floor(x / TILE_SIZE)] == 3)
	{
		door = get_door(&cub->doors, x, y);
		if (!door)
			return (1);
		x_distace = door->x * TILE_SIZE - cub->player->pos.x;
		y_distace = door->y * TILE_SIZE - cub->player->pos.y;
		if (door->is_facingx && door->y * TILE_SIZE >= y + TILE_SIZE * door->progress)
			return (0);
		if (!door->is_facingx && door->x * TILE_SIZE >= x + TILE_SIZE * door->progress)
			return (0);
		else
			return (1);
	}
	return (0);
}

void    arrow_handler(keys_t key, t_cub3D *cub)
{
	if (key == MLX_KEY_W)
		cub->player->walk_direction = 1;
	else if (key == MLX_KEY_S)
		cub->player->walk_direction = -1;
	else if (key == MLX_KEY_A)
		cub->player->walk_direction = -1;
	else if (key == MLX_KEY_D)
		cub->player->walk_direction = 1;
	else if (key == MLX_KEY_LEFT)
		cub->player->turn_direction = 1;
	else if (key == MLX_KEY_RIGHT)
		cub->player->turn_direction = -1;
}

void    key_handler(mlx_key_data_t key, void* param)
{
	t_cub3D *cub;

	cub = (t_cub3D *)param;
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
		arrow_handler(key.key, cub);
	}
}

void mouse_handler(double xpos, double ypos, void* param)
{
    t_cub3D *cub;
	(void)ypos;

	cub = (t_cub3D *)param;
	mlx_set_cursor_mode(cub->__mlx, MLX_MOUSE_HIDDEN);
	if (cub->cursor_hidden && cub->player->prev_x > xpos)
		cub->player->angle -= fabs(cub->player->prev_x - xpos) * 0.004;
	else if (cub->cursor_hidden && cub->player->prev_x < xpos)
		cub->player->angle += fabs(cub->player->prev_x - xpos) * 0.004;
	cub->player->prev_x = xpos;
}
