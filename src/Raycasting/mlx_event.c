/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:15:02 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/06 17:45:39 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int     wall(t_cub3D *cub, double x, double y)
{
	if (x < 0 || x >= cub->screen_width || y < 0 || y >= cub->screen_height)
		return (1);
	return (cub->map->map[(int)floor(y / TILE_SIZE)][(int)floor(x / TILE_SIZE)] == 1);
}

void    arrow_handler(keys_t key, t_cub3D *cub)
{
	double xpos[2];
	double ypos[2];
	
	cub->player->angle = remainder(cub->player->angle, 2 * M_PI);
	if (cub->player->angle < 0)
		cub->player->angle += 2 * M_PI;
	xpos[0] = SPEED * cos(cub->player->angle);
	xpos[1] = SPEED * cos(cub->player->angle + M_PI / 2);
	ypos[0] = SPEED * sin(cub->player->angle);
	ypos[1] = SPEED * sin(cub->player->angle + M_PI / 2);
	if (key == MLX_KEY_W && !wall(cub, cub->player->pos.x + xpos[0], cub->player->pos.y + ypos[0]))
	{
		cub->player->pos.x += xpos[0];
		cub->player->pos.y += ypos[0]; 
	}
	else if (key == MLX_KEY_S && !wall(cub, cub->player->pos.x - xpos[0], cub->player->pos.y - ypos[0]))
	{
		cub->player->pos.x -= xpos[0];
		cub->player->pos.y -= ypos[0]; 
	}
	else if (key == MLX_KEY_A && !wall(cub, cub->player->pos.x - xpos[1], cub->player->pos.y - ypos[1]))
	{
		cub->player->pos.x -= xpos[1];
		cub->player->pos.y -= ypos[1]; 
	}
	else if (key == MLX_KEY_D && !wall(cub, cub->player->pos.x + xpos[1], cub->player->pos.y + ypos[1]))
	{
		cub->player->pos.x += xpos[1];
		cub->player->pos.y += ypos[1]; 
	}
	else if (key == MLX_KEY_LEFT)
		cub->player->angle -= 0.005 * ROTATION_SPEED;
	else if (key == MLX_KEY_RIGHT)
		cub->player->angle += 0.005 * ROTATION_SPEED;
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
			cub->intro_img = cub->__img;
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
