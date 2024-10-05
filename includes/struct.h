/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:29:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/05 12:19:08 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define SCREEN_WIDTH	1080
# define SCREEN_HEIGHT	720
# define FOV_ANGLE (60 * (M_PI / 180))
# define TILE_SIZE	32
# define ORANGE	0xFFA500FF
# define BLACK	0x000000FF
# define WHITE	0xFFFFFFFF
# define RED	0xFF0000FF
# define SPEED 10
# define ROTATION_SPEED 15
# define NORD 3 * M_PI / 2
# define SOUTH M_PI / 2
# define EAST 0
# define WEAST M_PI
# define UP 0
# define DOWN 1
# define RIGHT 2
# define LEFT 3

/***********  STRUCT TYPEDEF  **********/
typedef struct s_parser 	t_parser;
typedef struct s_map_info	t_map_info;
typedef struct s_map		t_map_render;
typedef struct s_vect		t_vect;
typedef struct s_player 	t_player;
typedef struct s_cub		t_cub3D;
typedef struct s_Ray		t_Ray;
typedef struct s_door		t_door;

/***********  STRUCT PARSING  **********/
struct s_parser
{
	char			*line;
	int				min;
	int				max;
	t_map_info		*map_info;
	struct s_parser	*next;
	struct s_parser	*prev;
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
	int			**map;
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
	int			prev_x;
	short int	rot_speed;
	double		angle;
} ;

struct s_door
{
	int		x;
	int		y;
	size_t		timer;
	bool	is_open;
	bool	is_opening;
	bool	is_closing;
	double		progress;
	t_door	*next;
} ;

/***********  PROJECT GOLABL STRUCT  **********/
struct s_Ray {
    double		rayAngle;
	t_vect		wall_hit;
    double		distance;
    bool		hit_ver;
    int			wall_content;
};

struct s_cub
{
	mlx_t			*__mlx;
	mlx_image_t		*__img;
	t_parser		*parser;
	t_map_render	*map;
	t_player		*player;
	t_vect			*h_ray;
	t_vect			*v_ray;
	t_Ray			*rays;
	t_door			*doors;
	double			delta_time;
	int				max_width;
	int				max_height;
	int				screen_width;
	int				screen_height;
	bool				cursor_hidden;
} ;

#endif
