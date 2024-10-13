/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:29:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/13 20:29:45 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
