/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslibft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:18:48 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/13 14:51:10 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*ms_lstnew(int type, void *content)
{
	t_map	*lst;

	lst = ft_calloc(sizeof(t_map), 1);
	if (!lst)
		return (NULL);
	lst->line = content;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}

void	ms_lstadd_back(t_map **lst, t_map *new)
{
	t_map	*tmp;

	tmp = ms_lstlast(*lst);
	if (!tmp)
		*lst = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

t_map	*ms_lstlast(t_map *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}

int	ms_lstsize(t_map *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
