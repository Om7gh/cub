/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 07:44:58 by ialdidi           #+#    #+#             */
/*   Updated: 2024/10/09 10:25:51 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (printf("error here"), NULL);
	new = (char *)o_malloc(sizeof(char) * (len - start + 1), 0);
	if (!new)
		return (NULL);
	while (start + i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	return (new[i] = '\0', new);
}
