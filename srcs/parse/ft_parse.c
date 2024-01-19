/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:10:10 by segurbuz          #+#    #+#             */
/*   Updated: 2024/01/19 07:22:27 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_with_p_dir(t_map	*map, bool *flag, int *found)
{
	t_map	*temp;
	int		i;

	(void)flag;
	temp = map;
	i = -1;
	while (temp->line[++i])
	{
		if (temp->line[i] == 'E' || temp->line[i] == 'W'
			|| temp->line[i] == 'N' || temp->line[i] == 'S')
			(*found) += 1;
	}
}

bool	which_select_parse2(t_map *map, bool *flag)
{
	bool	check;
	int		found;
	t_map	*tmp;

	check = true;
	found = 0;
	tmp = map;
	while (tmp && *flag == false)
	{
		if ((tmp->line[0] == '\0' || tmp->line[0] == '\n')
			&& ft_strlen(tmp->line) <= 1 && check)
		{
			tmp = tmp->next;
			continue ;
		}
		check = false;
		map_find_space_in_content(tmp, &flag);
		map_invalid_char(tmp->line, &flag);
		map_left_wall_check(tmp, &flag);
		parse_with_p_dir(tmp, flag, &found);
		tmp = tmp->next;
	}
	if (found != 1)
		(*flag) = true;
	return (*flag);
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
		else if (map_find_attr(tmp->line, "F") || map_find_attr(tmp->line, "C"))
			parse_with_color(tmp->line, &flag, &check);
		else
			invalid_char2(tmp, &flag);
		tmp = tmp->next;
		if (check == 6)
			if (where_attr_map(tmp, &flag))
				break ;
	}
	return (flag);
}

void	ft_parse(t_data *data)
{
	bool	flag;

	flag = false;
	read_map(data);
	check_file_name(data->map_arg);
	if (which_select_parse(data))
		ft_error();
	map_attr_add_data(data);
	if (which_select_parse2(data->attr->map, &flag))
		ft_error();
}
