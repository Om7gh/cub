/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:44:24 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/06 15:24:11 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int is_facing(double angle)
{
    if (angle >= M_PI && angle <= M_PI * 2)
        return (UP);
    else if (angle >= 0 && angle <= M_PI)
        return (DOWN);
    else if (angle >= M_PI / 2 && angle <= M_PI * 1.5)
        return (LEFT);
    return (RIGHT);
}

void	open_door(t_cub3D *cub)
{
	// loop through the doors and check if the player is near a door and facing it
	// if the player is near a door and facing it, start the door opening animation
	if (!cub->doors->is_open)
		cub->doors->is_opening = 1;
	// wait for the door to open then start the timer of closing the door if the player is far enough from the door
}

void	close_door_animation(t_cub3D *cub)
{
    if (cub->doors->timer + 5000 < get_current_time())
        cub->doors->is_closing = 1;
    if (cub->doors->is_closing)
    {
        if (cub->doors->progress >= 1)
        {
            cub->doors->progress = 1;
            cub->doors->is_closing = 0;
            cub->doors->is_open = 0;
        }
    }
}
