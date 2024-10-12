/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:29:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 17:01:45 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define SCREEN_WIDTH	1080
# define SCREEN_HEIGHT	720
# define FOV_ANGLE (70 * (M_PI / 180))
# define T_L	60
# define ORANGE	0xFFA500FF
# define BLACK	0x000000FF
# define WHITE	0xFFFFFFFF
# define RED	0xFF0000FF
# define SPEED 4
# define ROTATION_SPEED 0.05
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
typedef struct s_enemie		t_enemie;
typedef struct s_sprite_render	t_spirite_render;
typedef struct s_sprite		t_sprite;

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
	int		arrow;
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

struct s_enemie
{
	mlx_texture_t	*enemie;
	mlx_image_t	*enemie_img;
	struct s_enemie	*next;
};

struct s_sprite
{
    double x;
    double y;
    int texture;
};

struct s_sprite_render
{
    double spriteX;       // Translated X coordinate relative to player
    double spriteY;       // Translated Y coordinate relative to player
    double invDet;        // Inverse determinant of camera matrix
    double transformX;    // Transformed X position of the sprite in camera space
    double transformY;    // Transformed Y position of the sprite (depth)
    int spriteScreenX;    // X-coordinate on the screen
    int spriteHeight;     // Height of the sprite on screen
    int spriteWidth;      // Width of the sprite on screen
    int drawStartX;       // Starting X position for drawing
    int drawEndX;         // Ending X position for drawing
    int drawStartY;       // Starting Y position for drawing
    int drawEndY;         // Ending Y position for drawing
};

struct s_cub
{
	mlx_t			*__mlx;
	mlx_image_t		*__img;
	mlx_texture_t			*texture_no;
	mlx_texture_t			*texture_so;
	mlx_texture_t			*texture_ea;
	mlx_texture_t			*texture_we;
	mlx_texture_t			*intro;
	mlx_texture_t			*door_texture;
	mlx_image_t		*texture_img_no;
	mlx_image_t		*texture_img_so;
	mlx_image_t		*texture_img_ea;
	mlx_image_t		*texture_img_we;
	mlx_image_t		*intro_img;
	mlx_image_t		*door_img;
	uint32_t		*pixels;
	t_parser		*parser;
	t_sprite 		*sprites;
	t_spirite_render	*sprit_render;
	int 			numSprites;
	double 			ZBuffer[SCREEN_WIDTH];
	t_map_render	*map;
	t_player		*player;
	t_vect			*h_ray;
	t_vect			*v_ray;
	t_Ray			*rays;
	t_door			*doors;
	double			delta_time;
	int				hit_content_h;
	int				hit_enemie;
	int				hit_content_v;
	int				max_width;
	int				max_height;
	int				screen_width;
	int				screen_height;
	int				check_intro;
	bool				cursor_hidden;
	int				texture_x;
	double				step;
	double				texture_pos;
	double				distance;
	t_enemie			*enemie;
} ;

#endif
