/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:18:31 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/20 13:00:46 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	fill_row(t_parser *tmp, t_cub3D *cub, int i, int *j)
{
	if (tmp->line[*j] == '1')
		cub->map->map[i][*j] = 1;
	else if (tmp->line[*j] == '0')
		cub->map->map[i][*j] = 0;
	else if (player_character(tmp->line[*j]))
		cub->map->map[i][*j] = 2;
	(*j)++;
}

void	map_before_and_after(t_cub3D *cub)
{
	t_parser			*tmp;
	int		i;
	int		j;

	tmp = cub->parser;
	i = -1;
	cub->map->map = malloc(sizeof(int *) * (cub->max_height + 1));
	while (++i < cub->max_height)
		cub->map->map[i] = malloc(sizeof(int) * (cub->max_width + 1));
	i = 0;
	while (tmp)
	{
		j = 0;
		while (tmp->line[j])
			fill_row(tmp, cub, i, &j);
		j--;
		while (j < cub->max_width)
		{
			cub->map->map[i][j] = 1;
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	cub->map->map[i] = NULL;
}
