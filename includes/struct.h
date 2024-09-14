/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:29:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/14 15:12:00 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define SCREEN_WIDTH	1024
# define SCREEN_HEIGHT	720
# define TILE_SIZE	32
# define ORANGE	0xFFA500FF
# define BLACK	0x000000FF
# define WHITE	0xFFFFFFFF
# define RED	0xFF0000FF
# define SPEED 2
# define NORD 3 * M_PI / 2
# define SOUTH M_PI / 2
# define EAST 0
# define WEAST M_PI


/***********  STRUCT TYPEDEF  **********/
typedef struct s_parser 	t_parser;
typedef struct s_map_info	t_map_info;
typedef struct s_map		t_map_render;
typedef struct s_vect		t_vect;
typedef struct s_player 	t_player;
typedef struct s_cub		t_cub3D;

/***********  STRUCT PARSING  **********/
struct s_parser
{
	char		*line;
	int		min;
	int		max;
	t_map_info	*map_info;
	struct s_parser *next;
	struct s_parser *prev;
} ;

/***********  HOLD MAP DATA  **********/
struct s_map_info
{
	uint32_t	floor_color[3];
	uint32_t	ceiling_color[3];
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
} ;

/***********  DRAWING MAP  **********/
struct	s_map
{
	int	       **map;
	t_map_info	*map_info;
	t_parser	*parser;
} ;

/***********  CORDONNEE X, Y  **********/
struct	s_vect
{
	double		x;
	double		y;
} ;

/***************  PLAYER INFO  ****************/
struct	s_player
{
	t_vect		pos;
	short int		rot_speed;
	double		angle;
} ;

/***********  PROJECT GOLABL STRUCT  **********/
struct s_cub
{
	mlx_t			*__mlx;
	mlx_image_t		*__img;
	t_parser		*parser;
	t_map_render		*map;
	t_player		*player;
	t_vect			*h_ray;
	t_vect			*v_ray;
	unsigned int		max_width;
	unsigned int		max_height;
	unsigned int			screen_width;
	unsigned int			screen_height;
} ;

#endif
