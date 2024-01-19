/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:41:03 by segurbuz          #+#    #+#             */
/*   Updated: 2024/01/18 21:36:58 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_check(char c)
{
	if (c == ' ' || c == '\n' || c == '\0' || c == '\t')
		return (true);
	return (false);
}

void	found_and_implement(t_map *map, int i, bool **flag)
{
	if (is_check(map->line[i + 1]) || is_check(map->line[i - 1]))
		**flag = true;
	if (map->prev && is_check(map->prev->line[i]))
		**flag = true;
	if (map->next && is_check(map->next->line[i]))
		**flag = true;
	if (!map->next)
		**flag = true;
	if (!map->prev)
		**flag = true;
}

void	map_find_space_in_content(t_map *map, bool **flag)
{
	t_map	*tmp;
	int		i;

	tmp = map;
	i = -1;
	while (tmp->line[++i])
	{
		if (tmp->line[i] == '0' || tmp->line[i] == 'S' \
			|| tmp->line[i] == 'N' || tmp->line[i] == 'E' \
			|| tmp->line[i] == 'W')
			found_and_implement(tmp, i, flag);
	}
}
