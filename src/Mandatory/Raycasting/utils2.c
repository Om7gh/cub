/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:29:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/31 22:20:48 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	my_mlx_put_pixel(double x, double y, int color, t_cub3d *cub)
{
	if ((x < 0 || x >= cub->screen_height) && (y < 0 || y >= cub->screen_width))
		return ;
	mlx_put_pixel(cub->__img, x, y, color);
}

static long	no_overflow(int sign, unsigned long long n, int count)
{
	if ((n > INT_MAX || count > 10) && sign == -1)
		ft_error("invalid color\n");
	if ((n > INT_MAX || count > 10) && sign == 1)
		ft_error("invalid color\n");
	return (n * sign);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		count;
	int		sign;
	long	n;

	i = 0;
	count = 0;
	sign = 1;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
		ft_error("Error");
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ft_error("Error");
		n = (n * 10) + (str[i++] - '0');
		count++;
	}
	return (no_overflow(sign, n, count));
}
