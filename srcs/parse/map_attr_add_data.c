/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attr_add_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:43:31 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/17 04:17:26 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	attr_add_data2(enum e_map type, char *line, int *i)
{
	char	*str;
	int		fd;

	if (type == SOUTH || type == NORTH || type == WEST || type == EAST)
	{
		(*i) = 2;
		while (line[(*i)] && line[(*i)] == ' ')
			(*i)++;
		str = ft_substr(line, (*i), ft_strlen(line + (*i)) - 1);
		fd = open(str, O_RDONLY);
		free(str);
		if (fd < 0)
			ft_error();
		close(fd);
	}
}

void	attr_add_data(char *line \
	, t_map **texture, enum e_map type, int *check)
{
	int		i;
	int		j;
	char	color[12];

	i = 0;
	j = 0;
	*check += 1;
	attr_add_data2(type, line, &i);
	if (type == FLOOR || type == CEILING)
	{
		i = 1;
		while (line[i] && line[i] == ' ')
			i++;
	}
	while (line[i] && (type == FLOOR || type == CEILING))
	{
		if (ft_isdigit(line[i]) || line[i] == ',')
			color[j++] = line[i];
		i++;
	}
	color[j] = '\0';
	if ((type == FLOOR || type == CEILING))
		ms_lstadd_back(texture, ms_lstnew(type, ft_strdup(color)));
	else
		ms_lstadd_back(texture, ms_lstnew(type \
			, ft_substr(line, i, ft_strlen(line + i) - 1)));
}

void	num_limit_check2(t_map *tmp, char *color)
{
	if (ft_atoi(color) > 255)
		ft_error();
	free(color);
}

void	num_limit_check(t_map *color)
{
	t_map	*tmp;
	int		i;
	int		size;

	tmp = color;
	size = 0;
	while (tmp)
	{
		i = 0;
		while (1)
		{
			if (ft_isdigit(tmp->line[i]))
			{
				size++;
				i++;
				continue;
			}
			num_limit_check2(tmp, ft_substr(tmp->line, i - size, size));
			size = 0;
			i++;
			if (!tmp->line[i])
				break ;
		}
		tmp = tmp->next;
	}
}

void	map_add_data(char *line, t_map **map)
{
	int nl;

	nl = 0;
	if ((line[0] == '\0' || line[0] == '\n')
		&& ft_strlen(line) <= 1)
		return ;
	if (ft_strlen(line) - 1 == '\n')
		nl = 1;
	ms_lstadd_back(map, ms_lstnew(MAP, ft_substr(line, 0, ft_strlen(line) - nl)));
}

void	add_map_doublearray(char ***map, t_map *temp_map, t_data *data)
{
	int size;
	int x;
	int y;

	y = 0;
	size = ms_lstsize(temp_map);
	data->attr->map_y = size;
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
	(*map)[y] = NULL;
}

void	map_attr_add_data(t_data *data)
{
	t_map	*map;
	int		check;

	map = data->map_cub;
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
			map_add_data(map->line, &data->attr->map);
		map = map->next;
	}
	num_limit_check(data->attr->color);
	add_map_doublearray(&(data->attr->arr_map), data->attr->map, data);
}
