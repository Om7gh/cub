/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenhams.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:40:50 by omghazi           #+#    #+#             */
/*   Updated: 2024/09/15 19:02:40 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int     get_sign(int a, int b)
{
        if (a < b)
                return (1);
        return (-1);
}

void bresenhams(int from_x, int from_y, int to_x, int to_y, t_cub3D *cub, uint32_t color)
{
    int diff[2], step[2], error[2], pos[2];

    diff[0] = abs(to_x - from_x);
    diff[1] = abs(to_y - from_y);
    step[0] = get_sign(from_x, to_x);
    step[1] = get_sign(from_y, to_y);
    error[0] = diff[0] - diff[1];
    pos[0] = from_x;
    pos[1] = from_y;

    while (pos[0] != to_x || pos[1] != to_y)
    {
        my_mlx_put_pixel(pos[0], pos[1], color, cub);
        error[1] = 2 * error[0];
        if (error[1] > -diff[1]) {
            error[0] -= diff[1];
            pos[0] += step[0];
        }

        if (error[1] < diff[0]) {
            error[0] += diff[0];
            pos[1] += step[1];
        }
    }
}

