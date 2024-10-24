/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:29:14 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/24 17:41:15 by hbettal          ###   ########.fr       */
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
		(write(2, "Error\n", 6), exit(1));
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			(write(2, "Error\n", 6), exit(1));
		n = (n * 10) + (str[i++] - '0');
		count++;
	}
	return (no_overflow(sign, n, count));
}
