/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:27:06 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/13 21:28:44 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_texture_height(t_cub3d *cub, int x)
{
	int	height;

	if (cub->rays[x].wall_content == 3)
		height = cub->door_img->height;
	else
	{
		if (!cub->rays[x].hit_ver && !(cub->rays[x].rayangle >= 0 \
		&& cub->rays[x].rayangle <= M_PI))
			height = cub->texture_img_no->height;
		else if (!cub->rays[x].hit_ver && (cub->rays[x].rayangle >= 0 \
		&& cub->rays[x].rayangle <= M_PI))
			height = cub->texture_img_so->height;
		else if (cub->rays[x].hit_ver && cub->rays[x].rayangle <= 1.5 * M_PI \
		&& cub->rays[x].rayangle >= 0.5 * M_PI)
			height = cub->texture_img_ea->height;
		else
			height = cub->texture_img_we->height;
	}
	return (height);
}

int	get_texture_width(t_cub3d *cub, int x)
{
	int	width;

	if (cub->rays[x].wall_content == 3)
		width = cub->door_img->width;
	else
	{
		if (!cub->rays[x].hit_ver && !(cub->rays[x].rayangle >= 0 \
		&& cub->rays[x].rayangle <= M_PI))
			width = cub->texture_img_no->width;
		else if (!cub->rays[x].hit_ver && (cub->rays[x].rayangle >= 0 \
		&& cub->rays[x].rayangle <= M_PI))
			width = cub->texture_img_so->width;
		else if (cub->rays[x].hit_ver && cub->rays[x].rayangle <= 1.5 * M_PI \
		&& cub->rays[x].rayangle >= 0.5 * M_PI)
			width = cub->texture_img_ea->width;
		else
			width = cub->texture_img_we->width;
	}
	return (width);
}
