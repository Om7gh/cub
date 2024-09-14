/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:56:34 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/14 11:11:17 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    my_mlx_put_pixel(unsigned int x, unsigned int y, int color, t_cub3D *cub)
{
        if ((x < 0 || x >= cub->screen_height) && (y < 0 || y >= cub->screen_width))
                return ;
        mlx_put_pixel(cub->__img, x, y, color);
}

void    render_2d(t_cub3D *cub)
{
        unsigned int     x;
        unsigned int     y;
        double xpos;
        double ypos;

        y = 0;
         cub->__img = mlx_new_image(cub->__mlx, cub->screen_width, cub->screen_height);
        if (!cub->__img)
        {
                printf("%s\n", mlx_strerror(MLX_INVIMG));
                exit(1);
        }
        mlx_image_to_window(cub->__mlx, cub->__img, 0, 0);
        while (y < cub->screen_height)
        {
                x = 0;
                while (x < cub->screen_width)
                {
                        if (cub->map->map[y / TILE_SIZE][x / TILE_SIZE] == 1)
                                my_mlx_put_pixel(x, y, ORANGE, cub);
                        else
                                my_mlx_put_pixel(x, y, BLACK, cub);
                        x++;
                }
                y++;
        }
        xpos = cub->player->pos.x + cos(cub->player->angle) * 1000;
        ypos = cub->player->pos.y + sin(cub->player->angle) * 1000;
        bresenhams(cub->player->pos.x, cub->player->pos.y, xpos, ypos, cub, WHITE);
}
