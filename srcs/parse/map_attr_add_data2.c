/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attr_add_data2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:42:57 by segurbuz          #+#    #+#             */
/*   Updated: 2024/01/19 06:43:12 by segurbuz         ###   ########.fr       */
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

void	attr_add_data3(enum e_map type, char *line, int *i)
{
	if (type == FLOOR || type == CEILING)
	{
		(*i) = 1;
		while (line[(*i)] && line[(*i)] == ' ')
			(*i)++;
	}
}

void	attr_add_data(char *line \
	, t_map **texture, enum e_map type, int *check)
{
	int		i;
	int		j;
	char	*color;

	i = 0;
	j = 0;
	color = malloc(sizeof(char) * (ft_strlen(line + i) + 1));
	*check += 1;
	attr_add_data2(type, line, &i);
	attr_add_data3(type, line, &i);
	while (line[i] && (type == FLOOR || type == CEILING))
	{
		if (ft_isdigit(line[i]) || line[i] == ',')
			color[j++] = line[i];
		i++;
	}
	color[j] = '\0';
	if ((type == FLOOR || type == CEILING))
		ms_lstadd_back(texture, ms_lstnew(type, ft_substr(color, 0, j)));
	else
		ms_lstadd_back(texture, ms_lstnew(type \
			, ft_substr(line, i, ft_strlen(line + i) - 1)));
	free(color);
}
