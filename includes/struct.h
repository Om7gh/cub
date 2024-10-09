/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:29:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/09 09:38:16 by hbettal          ###   ########.fr       */
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
# define ROTATION_SPEED 0.01
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
	const char		*no_texture;
	const char		*so_texture;
	const char		*we_texture;
	const char		*ea_texture;
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
	t_vect	pos;
	int		prev_x;
	double	angle;
	int		walk_direction;
	int		turn_direction;	
} ;

struct s_door
{
	int		x;
	int		y;
	size_t		timer;
	bool	is_open;
	bool	is_opening;
	bool	is_closing;
	bool	is_facingx;
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
	mlx_texture_t			*texture;
	mlx_texture_t			*intro;
	mlx_texture_t			*door_texture;
	mlx_image_t		*texture_img;
	mlx_image_t		*intro_img;
	mlx_image_t		*door_img;
	uint32_t		*pixels;
	t_parser		*parser;
	t_map_render	*map;
	t_player		*player;
	t_vect			*h_ray;
	t_vect			*v_ray;
	t_Ray			*rays;
	t_door			*doors;
	double			delta_time;
	int				hit_content_h;
	int				hit_content_v;
	int				max_width;
	int				max_height;
	int				screen_width;
	int				screen_height;
	int				check_intro;
	bool				cursor_hidden;
} ;

#endif
