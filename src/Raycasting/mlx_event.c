/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:15:02 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/30 22:07:19 by hbettal          ###   ########.fr       */
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
                cub->player->angle -= 0.1;
        else if (key == MLX_KEY_RIGHT)
                cub->player->angle += 0.1;
        else
                return ;
        mlx_delete_image(cub->__mlx, cub->__img);
        render_3d(cub);
}

void    key_handler(mlx_key_data_t key, void* param)
{
        t_cub3D *cub;

        cub = (t_cub3D *)param;
        if (key.key == MLX_KEY_ESCAPE)
        {
                mlx_close_window(cub->__mlx);
                mlx_terminate(cub->__mlx);
                exit(0);
        }
        arrow_handler(key.key, cub);
}
