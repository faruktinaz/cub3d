/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:06:42 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/19 02:13:05 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	set_player_angle_2(t_data *data, int x, int j)
{
	if (data->attr->arr_map[x][j] == 'E')
		data->var.pa = 0;
	else if (data->attr->arr_map[x][j] == 'W')
		data->var.pa = 3.1;
	else if (data->attr->arr_map[x][j] == 'N')
		data->var.pa = 4.8;
	else if (data->attr->arr_map[x][j] == 'S')
		data->var.pa = 1.5;
	data->attr->arr_map[x][j] = '0';
}

void	set_player_angle(t_data *data)
{
	int		x;
	int		j;

	x = 0;
	j = 0;
	while (data->attr->arr_map[x])
	{
		j = 0;
		while (data->attr->arr_map[x][j] &&
			data->attr->arr_map[x][j] != 'E' &&
			data->attr->arr_map[x][j] != 'S' &&
			data->attr->arr_map[x][j] != 'W' &&
			data->attr->arr_map[x][j] != 'N')
			j++;
		if (data->attr->arr_map[x][j] == 'E' ||
			data->attr->arr_map[x][j] == 'S' ||
			data->attr->arr_map[x][j] == 'W' ||
			data->attr->arr_map[x][j] == 'N')
		{
			set_player_angle_2(data, x, j);
			break ;
		}
		x++;
	}
}
