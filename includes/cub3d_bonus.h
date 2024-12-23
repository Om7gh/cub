/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:02:42 by omghazi           #+#    #+#             */
/*   Updated: 2024/11/01 21:03:49 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <libft.h>
# include ".MLX42.h"
# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <fcntl.h>
# include "struct_bonus.h"

/***********  PARSING  **********/
int				wall_character(int c);
int				player_character(int c);
int				check_extra_info(char *line);
int				color_process(char *line, uint32_t *color);
int				get_color(t_map_info *map, char c);
void			apply_shadow(uint32_t *color, double distance, \
	double max_distance);
void			check_texture_angle(t_cub3d *cub, int x, \
	mlx_image_t **current_texture);
uint32_t		get_texture_pixel(mlx_image_t *texture, int x, int y);
void			draw_floor_ceil(t_vect from, t_vect to, t_cub3d *cub);
char			*add_texture_path(char *line, int *checker);
void			check_point_side(t_parser *tmp, int i);
void			last_line_process(t_parser *parser);
void			first_line_process(t_parser *parser);
void			parse_map(t_parser *parser, t_cub3d *cub3d);
void			map_analyzer(t_parser **parser, t_map_info \
	*map_info, char *file);
void			check_map_data(char *line, int *checker, t_map_info *map_info);
int				get_max_width(t_parser *parser);
int				get_max_height(t_parser *parser);
void			map_before_and_after(t_cub3d *cub);
void			insert_node(int *flag, t_parser *node, \
	t_parser **parser, char *line);
void			insert_last(t_parser **parser_list, t_parser *new_node);
void			check_file_extension(char *file);
void			ft_error(char *str);
t_parser		*new_parser_node(char *line, int min, int max);
void			mini_map(t_cub3d *cub);
void			init_settings(t_cub3d *cub);
void			bresenhams(t_vect from, t_vect to, \
	t_cub3d *cub, uint32_t color);
void			my_mlx_put_pixel(double x, double y, int color, t_cub3d *cub);
mlx_image_t		*my_mlx_texture_to_img(t_cub3d *cub, mlx_texture_t *texture);
mlx_texture_t	*my_mlx_load_png( const char *path, t_cub3d *cub);
void			init_wall_texture(t_cub3d *cub);
void			key_handler(mlx_key_data_t key, void *param);
void			mouse_handler(double xpos, double ypos, void *param);
size_t			get_current_time(void);
void			open_door_animation(t_cub3d *cub);
void			close_door_animation(t_cub3d *cub);
void			open_door(t_cub3d *cub);
long			ft_atoi(const char *str);

/* FUNCTIONS */
int				wall(t_cub3d *cub, double x, double y);
void			render_3d(t_cub3d *cub);
void			find_vertical_intersx(t_cub3d *cub, \
	double angle, t_vect *check);
void			find_horizontal_intersx(t_cub3d *map, \
	double angle, t_vect *check);
t_door			*new_door(int x, int y);
void			fill_door_list(t_door **door, t_door *new_door);
t_door			*get_door(t_door **door, double x, double y);
void			get_door_info(t_cub3d *cub, t_door **door);
void			load_sprit_image(t_cub3d *cub);
int				get_texture_height(t_cub3d *cub, int x);
int				get_texture_width(t_cub3d *cub, int x);
void			load_sprit_texture(t_cub3d *cub);
void			move_player(t_cub3d *cub);
void			ft_clear_image(mlx_image_t *img);
void			close_files( void );
void			render_minimap(t_cub3d *cube);

#endif
