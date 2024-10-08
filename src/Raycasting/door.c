/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:44:24 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/08 14:43:58 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int is_facing(double angle)
{
    if (angle >= M_PI * 1.25 && angle <= M_PI * 1.75)
        return (UP);
    else if (angle >= M_PI * 0.25 && angle <= M_PI * 0.75)
        return (DOWN);
    else if (angle >= M_PI * 1.25 && angle <= M_PI * 1.75)
        return (LEFT);
    return (RIGHT);
}

void	open_door(t_cub3D *cub)
{
    t_door    *door;

	// loop through the doors and check if the player is near a door and facing it
    if (cub->rays[SCREEN_WIDTH / 2].wall_content == 3 && cub->rays[SCREEN_WIDTH / 2].distance < TILE_SIZE * 2)
    {
        door = get_door(&cub->doors, floor(cub->rays[SCREEN_WIDTH / 2].wall_hit.x), floor(cub->rays[SCREEN_WIDTH / 2].wall_hit.y));
        if (door)
        {
            printf("Door is facing\n");
            if (!door->is_open)
                door->is_opening = 1;
        }
    }
	// if the player is near a door and facing it, start the door opening animation
	// if (!cub->doors->is_open)
	// 	cub->doors->is_opening = 1;
	// wait for the door to open then start the timer of closing the door if the player is far enough from the door
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
            door->progress -= 0.02;
            door->timer = get_current_time();
            printf("door x %d || door y %d | ->> Door progress %f\n", door->y * TILE_SIZE, door->x * TILE_SIZE, door->progress);
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
        if (door->timer + 3000 < get_current_time())
            door->is_closing = 1;
        if (door->is_closing)
        {
            door->progress += 0.02;
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
