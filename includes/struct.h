/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:29:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/01 10:20:02 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define SCREEN_WIDTH	1024
# define SCREEN_HEIGHT	720
# define FOV_ANGLE (60 * (M_PI / 180))
# define TILE_SIZE	40
# define ORANGE	0xFFA500FF
# define BLACK	0x000000FF
# define WHITE	0xFFFFFFFF
# define RED	0xFF0000FF
# define SPEED 3
# define ROTATION_SPEED 15
# define NORD 3 * M_PI / 2
# define SOUTH M_PI / 2
# define EAST 0
# define WEAST M_PI
#define TWO_PI 6.28318530717958647692528676655900576

/***********  STRUCT TYPEDEF  **********/
typedef struct s_parser 	t_parser;
typedef struct s_map_info	t_map_info;
typedef struct s_map		t_map_render;
typedef struct s_vect		t_vect;
typedef struct s_player 	t_player;
typedef struct s_cub		t_cub3D;
typedef struct s_Ray		t_Ray;

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
	short int	rot_speed;
	double		angle;
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
	int				max_width;
	int				max_height;
	int				screen_width;
	int				screen_height;
} ;

#endif
