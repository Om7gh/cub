/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:14:45 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/14 23:20:55 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	update_line(char **str)
{
	char	*tmp;

	tmp = *str;
	while (*tmp && *tmp != '\n')
		tmp++;
	if (*tmp == '\n' && *(tmp + 1))
	{
		tmp = ft_strdup(++tmp);
		if (!tmp)
			return ((void)(*str = NULL));
	}
	else
		tmp = NULL;
	*str = tmp;
}

static char	*create_line(char *str)
{
	char	*extracted_line;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i = i + 1 * (str[i] == '\n');
	extracted_line = (char *)o_malloc(i + 1, 0);
	i = 0;
	while (str[i])
	{
		extracted_line[i] = str[i];
		if (str[i++] == '\n')
			break ;
	}
	extracted_line[i] = '\0';
	return (extracted_line);
}

static void	append_line(char **str, char *buffer)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(tmp, buffer);
}

static void	read_line(int fd, char **str)
{
	char	*buffer;
	char	*nl;
	int		rd;

	nl = NULL;
	buffer = (char *)o_malloc((size_t)BUFFER_SIZE + 1, 0);
	while (!nl)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
			return ;
		buffer[rd] = '\0';
		nl = ft_strchr(buffer, '\n');
		append_line(str, buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;

	if (read(fd, NULL, 0) < 0)
		return (NULL);
	if (!str || !ft_strchr(str, '\n'))
		read_line(fd, &str);
	line = create_line(str);
	if (!line)
		return (str = NULL);
	update_line(&str);
	return (line);
}
