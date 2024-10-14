/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:04:42 by kael-ala          #+#    #+#             */
/*   Updated: 2024/09/24 11:44:01 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, int c)
{
	int	cnt;
	int	pre;

	cnt = 0;
	pre = 1;
	while (*s)
	{
		if (*s == c)
			pre = 1;
		else if (pre)
		{
			pre = 0;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static void	*free_memory(char **strs, int i)
{
	while (i--)
		free(strs[i]);
	free(strs);
	strs = NULL;
	return (NULL);
}

static char	**split(char **strs, char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			strs[i] = ft_freq_substr(s, 0, len);
			if (!strs[i])
				return (free_memory(strs, i));
			s += len;
			i++;
		}
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_freq_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = o_malloc(sizeof(char *) * ((count_words(s, c) + 1)), FREQ);
	return (split(strs, s, c));
}
