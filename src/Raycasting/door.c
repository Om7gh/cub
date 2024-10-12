/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:44:24 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/12 13:43:14 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	open_door(t_cub3D *cub)
{
    t_door    *door;

    if (cub->rays[SCREEN_WIDTH / 2].wall_content == 3 && cub->rays[SCREEN_WIDTH / 2].distance < T_L * 3)
    {
        door = get_door(&cub->doors, floor(cub->rays[SCREEN_WIDTH / 2].wall_hit.x), floor(cub->rays[SCREEN_WIDTH / 2].wall_hit.y));
        if (door)
            if (!door->is_open)
                door->is_opening = 1;
    }
}

void	open_door_animation(t_cub3D *cub)
{
    t_door    *door;

    if (!cub->doors)
        return ;
    door = cub->doors;
    while (door)
    {
        if (door->is_opening)
        {
            door->progress -= 0.015;
            door->timer = get_current_time();
            if (door->progress <= 0)
            {
                door->progress = 0;
                door->is_opening = 0;
                door->is_open = 1;
            }
        }
        door = door->next;
    }
}

void	close_door_animation(t_cub3D *cub)
{
    t_door    *door;

    if (!cub->doors)
        return ;
    door = cub->doors;
    while (door)
    {
        if (door->timer + 2500 < get_current_time())
            door->is_closing = 1;
        if (door->is_closing)
        {
            if ((int)ceil(cub->player->pos.x / T_L) != door->x || (int)ceil(cub->player->pos.y / T_L) != door->y)
                door->progress += 0.03;
            if (door->progress >= 1)
            {
                door->progress = 1;
                door->is_closing = 0;
                door->is_open = 0;
            }
        }
        door = door->next;
    }
}
