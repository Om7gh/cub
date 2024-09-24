/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenhams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:40:50 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/20 13:15:47 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int     get_sign(long a, long b)
{
        if (a < b)
                return (1);
        return (-1);
}

void bresenhams(long from_x, long from_y, long to_x, long to_y, t_cub3D *cub, uint32_t color)
{
    long diff[2], step[2], error[2], pos[2];

    diff[0] = labs(to_x - from_x);
    diff[1] = labs(to_y - from_y);
    step[0] = get_sign(from_x, to_x);
    step[1] = get_sign(from_y, to_y);
    error[0] = diff[0] - diff[1];
    pos[0] = from_x;
    pos[1] = from_y;

    while (pos[0] != to_x || pos[1] != to_y)
    {
        my_mlx_put_pixel(pos[0], pos[1], color, cub);
        error[1] = 2 * error[0];
        if (error[1] > -diff[1])
        {
            error[0] -= diff[1];
            pos[0] += step[0];
        }
        if (error[1] < diff[0])
        {
            error[0] += diff[0];
            pos[1] += step[1];
        }
    }
}

