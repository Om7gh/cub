/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:55:50 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/14 23:19:00 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_length(int num)
{
	int	cnt;

	cnt = 1;
	while (num / 10)
	{
		cnt++;
		num /= 10;
	}
	return (cnt + (num < 0));
}

char	*ft_itoa(int n)
{
	int		num;
	int		n_len;
	char	*str;

	num = n;
	n_len = number_length(num);
	str = (char *)ft_calloc((n_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (n_len)
	{
		str[--n_len] = (num % 10) * (1 - 2 * (num < 0)) + '0';
		num /= 10;
	}
	*str = *str - 3 * (n < 0);
	return (str);
}
