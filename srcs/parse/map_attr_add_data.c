/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attr_add_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:43:31 by segurbuz          #+#    #+#             */
/*   Updated: 2024/01/19 07:20:50 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	num_limit_check(int *color)
{
	if (color[0] > 255 || color[0] < 0 || color[1] > 255 \
		|| color[1] < 0 || color[2] > 255 || color[2] < 0)
		ft_error();
}

void	map_add_data(char *line, t_map **map, t_data *data)
{
	int		nl;

	nl = 0;
	if ((line[0] == '\0' || line[0] == '\n')
		&& ft_strlen(line) <= 1 && data->var.flag)
		return ;
	if (ft_strlen(line) > 1)
		data->var.flag = false;
	if (ft_strlen(line) - 1 == '\n')
		nl = 1;
	ms_lstadd_back(map, ms_lstnew(MAP \
		, ft_substr(line, 0, ft_strlen(line) - nl)));
}

char	*ms_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	len = -1;
	i = 0;
	while (s1[++len])
		str[len] = s1[len];
	while (s2[i])
		str[len++] = s2[i++];
	str[len] = '\0';
	free (s1);
	return (str);
}

void	add_map_doublearray(char ***map, t_map *temp_map, t_data *data)
{
	int	size;
	int	x;
	int	y;

	y = 0;
	size = ms_lstsize(temp_map);
	(*map) = malloc(sizeof(char *) * (size + 1));
	while (temp_map)
	{
		(*map)[y] = ft_strdup(temp_map->line);
		x = -1;
		while ((*map)[y][++x])
		{
			if ((*map)[y][x] == 'E' || (*map)[y][x] == 'W'
				|| (*map)[y][x] == 'N' || (*map)[y][x] == 'S')
			{
				data->p_x = (float)x * 64;
				data->p_y = (float)y * 64;
			}
		}
		y++;
		temp_map = temp_map->next;
	}
	(*map)[y - 1] = ms_strjoin((*map)[y - 1], "\n");
	(*map)[y] = NULL;
}

void	map_attr_add_data(t_data *data)
{
	t_map	*map;
	int		check;

	map = data->map_cub;
	data->var.flag = true;
	check = 0;
	while (map)
	{
		if (map_find_attr(map->line, "SO") && check != 6)
			attr_add_data(map->line, &(data->attr->texture), SOUTH, &check);
		else if (map_find_attr(map->line, "NO") && check != 6)
			attr_add_data(map->line, &(data->attr->texture), NORTH, &check);
		else if (map_find_attr(map->line, "EA") && check != 6)
			attr_add_data(map->line, &(data->attr->texture), EAST, &check);
		else if (map_find_attr(map->line, "WE") && check != 6)
			attr_add_data(map->line, &(data->attr->texture), WEST, &check);
		else if (map_find_attr(map->line, "C") && check != 6)
			attr_add_data(map->line, &(data->attr->color), CEILING, &check);
		else if (map_find_attr(map->line, "F") && check != 6)
			attr_add_data(map->line, &(data->attr->color), FLOOR, &check);
		else if (check == 6)
			map_add_data(map->line, &data->attr->map, data);
		map = map->next;
	}
	add_map_doublearray(&(data->attr->arr_map), data->attr->map, data);
}
