/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenhams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:40:50 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/12 20:51:06 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_sign(long a, long b)
{
	if (a < b)
		return (1);
	return (-1);
}

void	bresenhams(t_vect from, t_vect to, t_cub3d *cub, uint32_t color)
{
	long	diff[2];
	long	step[2];
	long	error[2];
	long	pos[2];

	diff[0] = labs((long)to.x - (long)from.x);
	diff[1] = labs((long)to.y - (long)from.y);
	step[0] = get_sign((long)from.x, (long)to.x);
	step[1] = get_sign((long)from.y, (long)to.y);
	error[0] = diff[0] - diff[1];
	pos[0] = (long)from.x;
	pos[1] = (long)from.y;
	while (pos[0] != (long)to.x || pos[1] != (long)to.y)
	{
		my_mlx_put_pixel(pos[0], pos[1], color, cub);
		error[1] = 2 * error[0];
		if (error[1] > -diff[1])
			1 && (error[0] -= diff[1], pos[0] += step[0]);
		if (error[1] < diff[0])
			1 && (error[0] += diff[0], pos[1] += step[1]);
	}
}
