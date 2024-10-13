/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:18:37 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/13 17:27:19 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	player_character(int c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 2);
}

int	wall_character(int c)
{
	return (c == '1' || c == ' ' || c == '\n');
}

void	first_line_process(t_parser *parser)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	if (!parser || !parser->line)
		ft_error("Error\nMap is empty");
	tmp = parser;
	while (tmp->line[i] && tmp->line[i] != '\n')
	{
		if (!wall_character(tmp->line[i]))
		{
			if (tmp->line[i] != '0' && !player_character(tmp->line[i]))
			{
				ft_putstr_fd("invalid character in map `", 2);
				ft_putchar_fd(tmp->line[i], 2);
				o_malloc(0, 1);
				ft_error("\nError\nInvalid map data");
			}
			(o_malloc(0, 1), ft_error("Error\nMap is not closed"));
		}
		i++;
	}
}

void	last_line_process(t_parser *parser)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	tmp = parser;
	while (tmp->line[i] && tmp->line[i] != '\n')
	{
		if (!wall_character(tmp->line[i]))
		{
			if (tmp->line[i] != '0' && !player_character(tmp->line[i]))
			{
				ft_putstr_fd("invalid character in map `", 2);
				ft_putchar_fd(tmp->line[i], 2);
				o_malloc(0, 1);
				ft_error("\nError\nInvalid map data");
			}
			(o_malloc(0, 1), ft_error("Error\nMap is not closed"));
		}
		i++;
	}
}

void	check_point_side(t_parser *tmp, int i)
{
	if (tmp->line[i + 1] != '1' && tmp->line[i + 1] != '0' && tmp->line[i + 1] \
	!= 'D' && !player_character(tmp->line[i + 1]))
		ft_error("Error1\nInvalid map");
	if (tmp->prev && tmp->prev->line && (tmp->prev->line[i] != '1' && \
	tmp->prev->line[i] != '0' && tmp->prev->line[i] != 'D' \
	&& !player_character(tmp->prev->line[i])))
		ft_error("Error2\nInvalid map");
	if (tmp->line[i - 1] != '1' && tmp->line[i - 1] != '0' && \
	!player_character(tmp->line[i - 1]) && tmp->line[i - 1] != 'D')
		ft_error("Error3\nInvalid map");
	if (tmp->next && (tmp->next->line[i] != '1' && tmp->next->line[i] != '0' \
	&& !player_character(tmp->next->line[i]) && tmp->next->line[i] != 'D'))
		ft_error("Error4\nInvalid map");
}
