/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_linked_list_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:48:07 by omghazi           #+#    #+#             */
/*   Updated: 2024/11/01 18:46:35 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

t_door	*new_door(int x, int y)
{
	t_door	*new_door;

	new_door = o_malloc(sizeof(t_door), 0);
	new_door->x = x;
	new_door->y = y;
	new_door->is_open = false;
	new_door->is_opening = false;
	new_door->is_closing = false;
	new_door->progress = 1;
	new_door->next = NULL;
	return (new_door);
}

void	fill_door_list(t_door **door, t_door *new_door)
{
	t_door	*head;

	if (!door)
		return ;
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
