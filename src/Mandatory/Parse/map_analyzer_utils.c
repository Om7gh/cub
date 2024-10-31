/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:09:03 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/21 10:11:35 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	insert_node(int *flag, t_parser *node, t_parser **parser, char *line)
{
	*flag = 1;
	node = new_parser_node(line, 0, ft_strlen(line) - 1);
	insert_last(parser, node);
}

char	*add_texture_path(char *line, int *checker)
{
	char	*texture;

	texture = ft_strtrim(ft_strdup(line + 2), " ");
	(*checker)++;
	return (texture);
}

void	check_color_process(char *splited_line)
{
	int	i;

	i = 0;
	while (ft_isdigit(splited_line[i]) || splited_line[i] == ' ')
		i++;
	if (splited_line[i] != '\0')
		ft_error("Error\nInvalid color");
}

int	color_process(char *line, uint32_t *color)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	line = ft_strtrim(line, " ");
	tab = ft_split(line + 2, ',');
	while (tab[i])
	{
		j = 0;
		tab[i] = ft_strtrim(tab[i], "\n");
		tab[i] = ft_strtrim(tab[i], " ");
		if (ft_strlen(tab[i]) == 0 || tab[i][0] == '\0')
			ft_error("Error\nInvalid Color");
		check_color_process(tab[i]);
		color[i] = ft_atoi(tab[i]);
		if (color[i] < 0 || color[i] > 255)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}
