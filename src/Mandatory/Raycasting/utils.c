/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:35:29 by hbettal           #+#    #+#             */
/*   Updated: 2024/11/01 18:13:55 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

mlx_texture_t	*my_mlx_load_png( const char *path, t_cub3d *cub)
{
	mlx_texture_t	*text;

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
	if (!text_to_img)
	{
		printf("Error converting PNG texture to image.\n");
		mlx_terminate(cub->__mlx);
		o_malloc(0, 1);
		exit(1);
	}
	mlx_delete_texture(texture);
	return (text_to_img);
}
