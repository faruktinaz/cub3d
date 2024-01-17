/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:18:31 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/17 04:18:33 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	read_map(t_data *data)
{
	int		fd;
	char	*map;

	fd = open(data->map_arg, O_RDONLY);
	if (fd == -1)
		ft_error();
	while (1)
	{
		map = get_next_line(fd);
		if (!map)
		{
			free(map);
			break ;
		}
		ms_lstadd_back(&data->map_cub, ms_lstnew(MAP, ft_strdup(map)));
		free(map);
	}
	close(fd);
}

void	read_map_2(t_data *data, t_map *map, enum e_map type)
{
	int		fd;
	char	*emap;

	fd = open(data->map_arg, O_RDONLY);
	if (fd < 0)
		ft_error();
	while (1)
	{
		emap = get_next_line(fd);
		if (!emap)
		{
			free(emap);
			break ;
		}
		ms_lstadd_back(&map, ms_lstnew(type, ft_strdup(emap)));
		free(emap);
	}
	close(fd);
}

void	find_tab_in_map(t_map *map, bool *flag)
{
	int	i;

	i = -1;
	while (map->line[++i])
		if (map->line[i] == '\t')
			*flag = true;
}
