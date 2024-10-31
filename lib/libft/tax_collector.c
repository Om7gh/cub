/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tax_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:26:42 by kael-ala          #+#    #+#             */
/*   Updated: 2024/10/31 16:24:54 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	collect_address(t_collector **taxes)
{
	t_collector	*current;
	t_collector	*temp;

	if (!taxes || !*taxes)
		return ;
	current = *taxes;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->addr);
		free(temp);
	}
	*taxes = NULL;
}

t_collector	*new_addr(void *addr)
{
	t_collector	*new_addr;

	new_addr = malloc(sizeof(t_collector));
	if (!new_addr)
		return (NULL);
	new_addr->addr = addr;
	new_addr->next = NULL;
	return (new_addr);
}

static void	append_address(t_collector **taxes, t_collector *new)
{
	if (!new)
		return ;
	new->next = *taxes;
	*taxes = new;
}

void	*o_malloc(size_t size, int flag)
{
	static t_collector	*garbage;
	t_collector			*new;
	void				*addr;

	if (flag == 0)
	{
		addr = malloc(size);
		if (!addr)
		{
			collect_address(&garbage);
			exit (0);
		}
		new = new_addr(addr);
		if (!new)
		{
			collect_address(&garbage);
			exit (0);
		}
		append_address(&garbage, new);
		return (addr);
	}
	else
		return (collect_address(&garbage), NULL);
}
