/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keopsfenks <keopsfenks@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:31:44 by segurbuz          #+#    #+#             */
/*   Updated: 2023/12/05 01:32:37 by keopsfenks       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	map_find_attr(char *line, char *find)
{
	int	i;
	int	size;

	i = -1;
	size = ft_strlen(find);
	while (line[++i] != '\0')
	{
		if (size == 2)
			if (line[i] == find[0] \
				&& line[i + 1] == find[1])
				return (true);
		if (size == 1)
			if (line[i] == find[0])
				return (true);
	}
	return (false);
}

void	parse_with_map_content(char *line, bool *flag, int *check)
{
	int	flag2;

	flag2 = 1;
	if (ft_strncmp(line, "SO", 2) == 0 || ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		*check += 1;
		flag2 = 0;
	}
	if (*(line + 2) != ' ')
		*flag = true;
	if (flag2 == 1)
		*flag = true;
}

void	parse_with_color(char *line, bool *flag, int *rule)
{
	int	i;
	int	check;
	int	digit_check;

	check = 0;
	digit_check = 0;
	i = -1;
	parse_with_color2(line, &check, rule, flag);
	while (line[++i] != '\0')
		if (ft_isdigit(line[i]))
			break ;
	check = 0;
	parse_with_color3(line, &digit_check, flag, &i);
	if (digit_check != 3)
		*flag = true;
}

void	map_invalid_char(char *line, bool **flag)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1' \
			&& line[i] != '0' && line[i] != 'N' \
			&& line[i] != 'S' && line[i] != 'E' \
			&& line[i] != 'W' && line[i] != '\n')
			**flag = true;
	}
}
