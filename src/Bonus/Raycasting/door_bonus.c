/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:44:24 by hbettal           #+#    #+#             */
/*   Updated: 2024/11/01 18:03:36 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	get_door_info(t_cub3d *cub, t_door **door)
{
	t_door	*new;
	int		x;
	int		y;

	y = -1;
	while (++y < cub->max_height)
	{
		x = -1;
		while (++x < cub->max_width)
		{
			if (cub->map->map[y][x] == 3)
			{
				new = new_door(x + 1, y + 1);
				if (cub->map->map[y - 1][x] == 1)
					new->is_facingx = 1;
				fill_door_list(door, new);
			}
		}
	}
}

t_door	*get_door(t_door **door, double x, double y)
{
	t_door	*tmp;

	if (!door)
		return (NULL);
	tmp = *door;
	while (tmp)
	{
		if (tmp->x * T_L - T_L <= x && tmp->x * T_L + T_L >= x \
		&& tmp->y * T_L - T_L <= y && tmp->y * T_L + T_L >= y)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	open_door(t_cub3d *cub)
{
	t_door	*door;

	if (cub->rays[SCREEN_WIDTH / 2].wall_content == 3 && \
	cub->rays[SCREEN_WIDTH / 2].distance < T_L * 3)
	{
		door = get_door(&cub->doors, \
		floor(cub->rays[SCREEN_WIDTH / 2].wall_hit.x), \
		floor(cub->rays[SCREEN_WIDTH / 2].wall_hit.y));
		if (door)
			if (!door->is_open)
				door->is_opening = 1;
	}
}

void	open_door_animation(t_cub3d *cub)
{
	t_door	*door;

	if (!cub->doors)
		return ;
	door = cub->doors;
	while (door)
	{
		if (door->is_opening)
		{
			door->progress -= 0.030;
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

void	close_door_animation(t_cub3d *cub)
{
	t_door	*door;

	if (!cub->doors)
		return ;
	door = cub->doors;
	while (door)
	{
		if (door->timer + 2500 < get_current_time())
			door->is_closing = 1;
		if (door->is_closing)
		{
			if ((int)ceil(cub->player->pos.x / T_L) != door->x \
			|| (int)ceil(cub->player->pos.y / T_L) != door->y)
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
