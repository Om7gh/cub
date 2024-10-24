/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:35:08 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/24 13:33:19 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	no_overflow(int sign, unsigned long long n, int count)
{
	if ((n > INT_MAX || count > 10) && sign == -1)
		(write(2, "invalid color\n", 14), exit(1));
	if ((n > INT_MAX || count > 10) && sign == 1)
		(write(2, "invalid color\n", 14), exit(1));
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
