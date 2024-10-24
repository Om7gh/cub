/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:13:22 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/24 15:37:26 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_error(char *str)
{
	int	i;

	i = 3;
	while (i <= 10200)
	{
		if (close(i) == -1)
			break ;
		i++;
	}
	ft_putendl_fd(str, 2);
	o_malloc(0, 1);
	exit(1);
}

void	check_file_extension(char *file)
{
	char	*extenstion;

	extenstion = ft_strrchr(file, '.');
	if (extenstion == NULL)
		ft_error("Error\nInvalid file extension");
	if (ft_strncmp(extenstion, ".cub", 4) != 0 || ft_strlen(extenstion) != 4)
		ft_error("Error\nInvalid file extension");
}

void	ft_clear_image(mlx_image_t *img)
{
	uint32_t		i;
	uint32_t		j;
	unsigned int	clear;

	i = 0;
	clear = 255 << 24 | 255 << 16 | 255 << 8 | 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, clear);
			j++;
		}
		i++;
	}
}

void	move_player(t_cub3d *cub)
{
	t_vect	next_pos;
	double	next_angle;

	next_pos.x = cub->player->pos.x + SPEED * \
	cos(cub->player->angle) * cub->player->walk_direction;
	next_pos.y = cub->player->pos.y + SPEED * \
	sin(cub->player->angle) * cub->player->walk_direction;
	next_angle = cub->player->angle + ROTATION_SPEED * \
	cub->player->turn_direction;
	cub->player->angle = next_angle;
	if (!wall(cub, next_pos.x + 5, next_pos.y) && \
	!wall(cub, next_pos.x - 5, next_pos.y))
		cub->player->pos = next_pos;
	if (cub->player->arrow != 0)
	{
		next_pos.x = cub->player->pos.x + SPEED * \
		cos(cub->player->angle + M_PI / 2) * cub->player->arrow;
		next_pos.y = cub->player->pos.y + SPEED * \
		sin(cub->player->angle + M_PI / 2) * cub->player->arrow;
		if (!wall(cub, next_pos.x + 5, next_pos.y) && \
		!wall(cub, next_pos.x - 5, next_pos.y))
			cub->player->pos = next_pos;
	}
}
