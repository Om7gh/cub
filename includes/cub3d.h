/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:42 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/09 12:55:40 by omghazi          ###   ########.fr       */
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
# include <sys/time.h>
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
void    mini_map(t_cub3D *cub);
void    init_settings(t_cub3D *cub);
void    bresenhams(long from_x, long from_y, long to_x, long to_y, t_cub3D *cub, uint32_t color);
void    my_mlx_put_pixel(double x, double y, int color, t_cub3D *cub);
void    key_handler(mlx_key_data_t key, void* param);
void	mouse_handler(double xpos, double ypos, void* param);
size_t	get_current_time();
void	open_door_animation(t_cub3D *cub);
void	close_door_animation(t_cub3D *cub);
void	open_door(t_cub3D *cub);

/* FUNCTIONS */
int     wall(t_cub3D *cub, double x, double y);
void    render_3d(t_cub3D *cub);
void	find_vertical_intersections(t_cub3D *cub, double angle, t_vect *check);
void	find_horizontal_intersections(t_cub3D *map, double angle, t_vect *check);
t_door  *new_door(int , int);
void    fill_door_list(t_door **door, t_door *new_door);
t_door	*get_door(t_door **door, double x, double y);

t_enemie        *new_enemie(const char *path, t_cub3D *cub);
void    	append_enemie(t_enemie **enemie, t_enemie *new_enemie);

#endif
