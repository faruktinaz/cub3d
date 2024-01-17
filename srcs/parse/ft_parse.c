/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:10:10 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/17 03:56:39 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_left_wall_check(t_map *map, bool **flag)
{
	int	i;

	i = 0;
	while (map->line[i] && map->line[i] == ' ')
		i++;
	if (map->line[i] != '1' && map->line[0] != '\n')
		**flag = true;
}

void	parse_with_p_dir(t_map	*map, bool *flag, int *found)
{
	t_map	*temp;
	int		i;

	temp = map;
	i = -1;
	while (temp->line[++i])
	{
		if (temp->line[i] == 'E' || temp->line[i] == 'W'
		|| temp->line[i] == 'N' || temp->line[i] == 'S')
			(*found) += 1;
	}
}

void	which_select_parse2(t_map *map, bool *flag)
{
	bool	check;
	int 	found;

	check = true;
	found = 0;
	while (map && *flag == false)
	{
		if ((map->line[0] == '\0' || map->line[0] == '\n')
			&& ft_strlen(map->line) <= 1 && check)
		{
			map = map->next;
			continue ;
		}
		check = false;
		map_find_space_in_content(map, &flag);
		map_invalid_char(map->line, &flag);
		map_left_wall_check(map, &flag);
		parse_with_p_dir(map, flag, &found);
		map = map->next;
	}
	if (found != 1)
		(*flag) = true;
}

bool	where_attr_map(t_map *map, bool *flag)
{
	while (map)
	{
		if ((map->line[0] == '\0' || map->line[0] == '\n')
			&& ft_strlen(map->line) <= 1)
		{
			map = map->next;
			continue ;
		}
		break ;
	}
	if (!map)
		return (*flag = true, true);
	if (map && map->line[0] == '\0')
		return (*flag = true, true);
	return (true);
}

bool	which_select_parse(t_data *data)
{
	t_map	*tmp;
	bool	flag;
	int		check;

	flag = false;
	check = 0;
	tmp = data->map_cub;
	while (tmp)
	{
		find_tab_in_map(tmp, &flag);
		if (map_find_attr(tmp->line, "SO")
			|| map_find_attr(tmp->line, "NO")
			|| map_find_attr(tmp->line, "WE")
			|| map_find_attr(tmp->line, "EA"))
			parse_with_map_content(tmp->line, &flag, &check);
		if (map_find_attr(tmp->line, "F") || map_find_attr(tmp->line, "C"))
			parse_with_color(tmp->line, &flag, &check);
		tmp = tmp->next;
		if (check == 6)
			if (where_attr_map(tmp, &flag))
				break ;
	}
	if (flag == false)
		which_select_parse2(tmp, &flag);
	return (flag);
}

void	check_file_name(char *name)
{
	int	len;

	len = (int)ft_strlen(name);
	if (len < 5)
		ft_error();
	if (name[len - 1] != 'b' || name[len - 2] != 'u' || name[len - 3] != 'c'
		|| name[len - 4] != '.')
		ft_error();
}

void	ft_parse(t_data *data)
{
	read_map(data);
	check_file_name(data->map_arg);
	if (which_select_parse(data))
		ft_error();
	map_attr_add_data(data);
}
