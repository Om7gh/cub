/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:35:29 by hbettal           #+#    #+#             */
/*   Updated: 2024/10/02 19:38:23 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double get_current_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

void  get_delta_time(double *last_time, t_cub3D *cub)
{
	double  current_time;
	double  delta_time;

	current_time = get_current_time();
	cub->delta_time = current_time - *last_time;
	*last_time = current_time;
}