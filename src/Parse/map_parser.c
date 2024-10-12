/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:17:48 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 20:32:45 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	get_max_width(t_parser *parser)
{
	t_parser	*tmp;
	int			i;

	tmp = parser;
	i = INT_MIN;
	while (tmp)
	{
		if (tmp->max >= i)
			i = tmp->max;
		tmp = tmp->next;
	}
	return (i);
}

static int	get_max_height(t_parser *parser)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	tmp = parser;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	is_map_closed(t_parser *tmp)
{
	int	i;

	while (tmp->next)
	{
		i = 1;
		while (tmp->line[i])
		{
			if ((tmp->line[0] != '1' || tmp->line[0] != ' ') \
				&& tmp->line[tmp->max - 1] != '1')
				(o_malloc(0, 1), ft_error("Error\nMap is not closed"));
			if (tmp->line[i] == '0')
				check_point_side(tmp, i);
			if (tmp->line[i] != '0' && !player_character(tmp->line[i]) \
				&& !wall_character(tmp->line[i]) && tmp->line[i] != 'D' && tmp->line[i] != 'A')
			{
				ft_putstr_fd("invalid character in map `", 2);
				ft_putchar_fd(tmp->line[i], 2);
				ft_error("\nError\nInvalid map data");
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	parse_door(t_parser *parser, int i)
{
	if (parser->line[i - 1] == '1')
	{
		if (parser->line[i + 1] != '1')
			ft_error("Error\nInvalid door");
	}
	else if (parser->prev->line[i] == '1')
	{
		if (parser->next->line[i] != '1')
			ft_error("Error\nInvalid door");
	}
	else if (parser->line[i + 1] == '1')
	{
		if (parser->line[i - 1] != '1')
			ft_error("Error\nInvalid door");
	}
	else if (parser->next->line[i] == '1')
	{
		if (parser->prev->line[i] != '1')
			ft_error("Error\nInvalid door");
	}
}

static void	check_player_space(t_parser *parser)
{
	t_parser	*tmp;
	int			i;
	int			flag;
	int			door_flag;
	int			enemie_flag;

	tmp = parser;
	flag = 0;
	door_flag = 0;
	enemie_flag = 0;
	while (tmp)
	{
		i = 0;
		if (tmp->line[0] == '\n')
			ft_error("Error\nInvalid map");
		while (tmp->line[++i])
		{
			if (tmp->line[i] == '0')
				check_point_side(tmp, i);
			if (tmp->line[i] == 'D')
				parse_door(tmp, i);
			if (player_character(tmp->line[i]))
				flag++;
			if (tmp->line[i] == 'A')
				enemie_flag++;
			if (tmp->line[i] == 'D')
				door_flag++;
		}
		tmp = tmp->next;
	}
	if (flag != 1)
		ft_error("Error\nPlayer not found or muti player exist");
	if (enemie_flag == 0)
		ft_error("Error\nenemie not found ");
	if (door_flag == 0)
		ft_error("Error\nDoor not found");
}

void	parse_map(t_parser *parser, t_cub3d *cub3d)
{
	t_parser	*tmp;

	first_line_process(parser);
	tmp = parser;
	is_map_closed(tmp->next);
	last_line_process(tmp);
	check_player_space(parser);
	cub3d->max_width = get_max_width(parser);
	cub3d->max_height = get_max_height(parser);
	cub3d->parser = parser;
	map_before_and_after(cub3d);
}
