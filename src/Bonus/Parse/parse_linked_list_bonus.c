/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_linked_list_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:06:04 by omghazi           #+#    #+#             */
/*   Updated: 2024/11/01 18:47:03 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

t_parser	*new_parser_node(char *line, int min, int max)
{
	t_parser	*parser;

	parser = o_malloc(sizeof(t_parser), 0);
	parser->line = ft_strdup(line);
	parser->min = min;
	parser->max = max;
	parser->next = NULL;
	parser->prev = NULL;
	return (parser);
}

void	insert_last(t_parser **parser_list, t_parser *new_node)
{
	t_parser	*tmp;

	if (!parser_list)
		return ;
	if (!*parser_list)
	{
		*parser_list = new_node;
		return ;
	}
	tmp = *parser_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}
