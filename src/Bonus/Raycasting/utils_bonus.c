/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:35:29 by hbettal           #+#    #+#             */
/*   Updated: 2024/11/01 21:03:41 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

void	load_sprit_texture(t_cub3d *cub)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	while (i < 180)
	{
		str = NULL;
		str = ft_strjoin(str, "sprite/");
		tmp = ft_itoa(i + 1);
		str = ft_strjoin(str, tmp);
		free(tmp);
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
	while (i < 180)
	{
		cub->sprite[i] = my_mlx_texture_to_img(cub, cub->sprit_text[i]);
		i++;
	}
}
