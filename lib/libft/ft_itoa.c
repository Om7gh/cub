/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:47:31 by ialdidi           #+#    #+#             */
/*   Updated: 2024/10/13 17:38:14 by omghazi          ###   ########.fr       */
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
	str = (char *)o_malloc((n_len + 1) * sizeof(char), 0);
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
