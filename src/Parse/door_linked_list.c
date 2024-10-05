/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:48:07 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/05 11:27:08 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_door  *new_door(int x, int y)
{
        t_door *new_door;

        new_door = malloc(sizeof(t_door));
        if (!new_door)
                return (NULL);
        new_door->x = x;
        new_door->y = y;
        new_door->is_open = false;
        new_door->is_opening = false;
        new_door->is_closing = false;
        new_door->progress = 1;
        new_door->next = NULL;
        return (new_door);
}

void    fill_door_list(t_door **door, t_door *new_door)
{
        t_door *head;

        if (!door)
                return;
        if (!*door)
        {
                *door = new_door;
                return ;
        }
        head = *door;
        while (head->next)
                head = head->next;
        head->next = new_door;
}
