/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analyzer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:08:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 20:57:40 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>      

void	check_map_data(char *line, int *checker, t_map_info *map_info)
{
	if (!ft_strncmp(ft_strtrim(line, " "), "NO ", 3))
		map_info->no_texture = add_texture_path(line, checker);
	else if (!ft_strncmp(ft_strtrim(line, " "), "SO ", 3))
		map_info->so_texture = add_texture_path(line, checker);
	else if (!ft_strncmp(ft_strtrim(line, " "), "WE ", 3))
		map_info->we_texture = add_texture_path(line, checker);
	else if (!ft_strncmp(ft_strtrim(line, " "), "EA ", 3))
		map_info->ea_texture = add_texture_path(line, checker);
	else if (!ft_strncmp(ft_strtrim(line, " "), "F ", 2))
	{
		if (color_process(ft_strtrim(line, " "), map_info->floor_color) == 0)
			(o_malloc(0, 1),ft_error("Error\nInvalid color"));
		(*checker)++;
	}
	else if (!ft_strncmp(ft_strtrim(line, " "), "C ", 2))
	{
		if (color_process(ft_strtrim(line, " "), map_info->ceiling_color) == 0)
			(o_malloc(0, 1),ft_error("Error\nInvalid color"));
		(*checker)++;
	}
}

int	check_extra_info(char *line)
{
	if (ft_strchr(line, 'N') && ft_strchr(line, 'O'))
		ft_error("Error\nInvalid map data");
	if (ft_strchr(line, 'F'))
		ft_error("Error\nInvalid map data");
	if (ft_strchr(line, 'S') && ft_strchr(line, 'O'))
		ft_error("Error\nInvalid map data");
	if (ft_strchr(line, 'W') && ft_strchr(line, 'E'))
		ft_error("Error\nInvalid map data");
	if (ft_strchr(line, 'E') && ft_strchr(line, 'A'))
		ft_error("Error\nInvalid map data");
	if (ft_strchr(line, 'C'))
		ft_error("Error\nInvalid map data");
	return (0);
}

int	skip_empty_lines(char **line, int fd, int flag)
{
	if (!ft_strchr(*line, '1') && !ft_strchr(*line, '0') \
				&& !ft_strchr(*line, 'N') && !flag)
	{
		*line = get_next_line(fd);
		return (1);
	}
	return (0);
}

void	map_analyzer(t_parser **parser, t_map_info *map_info, char *file)
{
	t_parser		*node;
	static int		checker;
	char			*line;
	int				fd;
	int				flag;

	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		(o_malloc(0, 1), ft_error("Error\nFile not found"));
	1 && (line = get_next_line(fd), flag = 0, node = NULL);
	while (line)
	{
		if (checker <= 5)
			check_map_data(line, &checker, map_info);
		else
		{
			check_extra_info(line);
			if (skip_empty_lines(&line, fd, flag))
				continue ;
			else
				insert_node(&flag, node, parser, line);
		}
		line = get_next_line(fd);
	}
	close(fd);
}
