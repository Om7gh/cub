/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:42 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/14 10:29:13 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include "MLX42.h"
# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "struct.h"

/***********  PARSING  **********/
int			wall_character(int c);
int			player_character(int c);
int			check_extra_info(char *line);
int			color_process(char *line, uint32_t *color);
char		*add_texture_path(char *line, int *checker);
void		check_point_side(t_parser *tmp, int i);
void		last_line_process(t_parser *parser);
void		first_line_process(t_parser *parser);
void		parse_map(t_parser *parser, t_cub3D *cub3d);
void		map_analyzer(t_parser **parser, t_map_info *map_info, char *file);
void		check_map_data(char *line, int *checker, t_map_info *map_info);
void		map_before_and_after(t_cub3D *cub);
void		insert_node(int *flag, t_parser *node, \
	t_parser **parser, char *line);
void		insert_last(t_parser **parser_list, t_parser *new_node);
void		check_file_extension(char *file);
void		ft_error(char *str);
t_parser	*new_parser_node(char *line, int min, int max);
void    render_2d(t_cub3D *cub);
void    init_settings(t_cub3D *cub);
void    bresenhams(int from_x, int from_y, int to_x, int to_y, t_cub3D *cub, uint32_t color);
void    my_mlx_put_pixel(unsigned int x, unsigned int y, int color, t_cub3D *cub);
void    key_handler(mlx_key_data_t key, void* param);


/* FUNCTIONS */
int     wall(t_cub3D *cub, int x, int y);

#endif
