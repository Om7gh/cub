/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:35:29 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/13 17:47:04 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_minimap_scale(t_cub3d *cub)
{
	double	scale;

	if (cub->screen_height > cub->screen_width)
		scale = (float)200 / (float)(cub->screen_height);
	else
		scale = (float)200 / (float)(cub->screen_width);
	cub->scale = scale;
}

mlx_texture_t	*my_mlx_load_png( const char *path, t_cub3d *cub)
{
	mlx_texture_t	*text;

	printf("%s\n", path);
	text = mlx_load_png(path);
	if (!text)
	{
		mlx_terminate(cub->__mlx);
		ft_error("Error loading .png texture.\n");
	}
	return (text);
}

mlx_image_t	*my_mlx_texture_to_img(t_cub3d *cub, mlx_texture_t *texture)
{
	mlx_image_t	*text_to_img;

	text_to_img = mlx_texture_to_image(cub->__mlx, texture);
	if (!cub->texture_img_no)
	{
		printf("Error converting PNG texture to image.\n");
		mlx_terminate(cub->__mlx);
		o_malloc(0, 1);
		exit(1);
	}
	return (text_to_img);
}

void	load_sprit_texture(t_cub3d *cub)
{
	int	i;
	char	*str;

	i = 0;
	while (i < 14)
	{
		str = NULL;
		str = ft_strjoin(str, "sprite/");
		str = ft_strjoin(str, ft_itoa(i + 1));
		str = ft_strjoin(str, ".png");
		cub->sprit_text[i] = my_mlx_load_png(str, cub);
		i++;
	}
}

void	load_sprit_image(t_cub3d *cub)
{
	int	i;

	load_sprit_texture(cub);
	i = 0;
	while (i < 14)
	{
		cub->sprite[i] = my_mlx_texture_to_img(cub, cub->sprit_text[i]);
		i++;
	}
}

void	my_mlx_put_pixel(double x, double y, int color, t_cub3d *cub)
{
	if ((x < 0 || x >= cub->screen_height) && (y < 0 || y >= cub->screen_width))
		return ;
	mlx_put_pixel(cub->__img, x, y, color);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	get_delta_time(double *last_time, t_cub3d *cub)
{
	double	current_time;

	current_time = get_current_time();
	cub->delta_time = current_time - *last_time;
	*last_time = current_time;
}
