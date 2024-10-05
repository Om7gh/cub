/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:13:22 by omghazi           #+#    #+#             */
/*   Updated: 2024/10/05 14:10:38 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	check_file_extension(char *file)
{
	char	*extenstion;

	extenstion = ft_strrchr(file, '.');
	if (extenstion == NULL)
		ft_error("Error\nInvalid file extension");
	if (ft_strncmp(extenstion, ".cub", 4) != 0 || ft_strlen(extenstion) != 4)
		ft_error("Error\nInvalid file extension");
}
