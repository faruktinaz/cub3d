/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_directions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:29:57 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/19 02:13:15 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	set_raycasting_dir2(t_data *data, int *i)
{
	if (data->wall_direction[(*i)] == 4)
	{
		data->var.wallcolor = get_pixel_in_texture(&data->textures[2], \
			(data->var.wall_y) * 64, data->var.walltes);
		img_pix_put(&data->image, data->var.k \
			, data->end_j, data->var.wallcolor);
	}
	else
	{
		data->var.wallcolor = get_pixel_in_texture(&data->textures[3] \
			, (data->var.wall_y) * 64, data->var.walltes);
		img_pix_put(&data->image, data->var.k \
			, data->end_j, data->var.wallcolor);
	}
}

void	set_raycasting_dir(t_data *data, int *i)
{
	if (data->wall_direction[(*i)] == 1)
		img_pix_put(&data->image, data->var.k \
			, data->end_j, data->var.wallcolor);
	else if (data->wall_direction[(*i)] == 3)
	{
		data->var.wallcolor = get_pixel_in_texture(&data->textures[1] \
			, (data->var.wall_x) * 64, data->var.walltes);
		img_pix_put(&data->image, data->var.k \
			, data->end_j, data->var.wallcolor);
	}
	else if (data->wall_direction[(*i)] == 2)
	{
		data->var.wallcolor = get_pixel_in_texture(&data->textures[3] \
			, (data->var.wall_y) * 64, data->var.walltes);
		img_pix_put(&data->image, data->var.k \
			, data->end_j, data->var.wallcolor);
	}
	else
		set_raycasting_dir2(data, i);
}

void	set_directions(t_data *data)
{
	if (data->attr->arr_map[(int)(data->var.y_d) / 64] \
		[(int)(data->var.x_d - 1) / 64] == '0' && \
		data->attr->arr_map[(int)(data->var.y_d + 1) / 64] \
			[(int)(data->var.x_d) / 64] == '1')
		data->direction = 2;
	else if (data->attr->arr_map[(int)(data->var.y_d) / 64]
		[(int)(data->var.x_d + 1) / 64] == '0' && \
		data->attr->arr_map[(int)(data->var.y_d - 1) / 64] \
			[(int)(data->var.x_d) / 64] == '1')
		data->direction = 4;
	else if (data->attr->arr_map[(int)(data->var.y_d + 1) / 64] \
		[(int)(data->var.x_d) / 64] == '0' && \
		data->attr->arr_map[(int)(data->var.y_d) / 64] \
			[(int)(data->var.x_d - 1) / 64] == '1')
		data->direction = 1;
	else if (data->attr->arr_map[(int)(data->var.y_d - 1) / 64]
		[(int)(data->var.x_d) / 64] == '0' && \
		data->attr->arr_map[(int)(data->var.y_d) / 64]
			[(int)(data->var.x_d + 1) / 64] == '1')
		data->direction = 3;
}

void	ray_sending(t_data *data)
{
	while (1)
	{
		if (data->attr->arr_map[(int)(data->var.y_d) / 64]
			[(int)(data->var.x_d) / 64] != '1' && data->attr->arr_map \
			[(int)(data->var.y_d) / 64][(int)(data->var.x_d) / 64] != '0')
			break ;
		else if (data->attr->arr_map[(int)(data->var.y_d) / 64] \
			[(int)(data->var.x_d) / 64] == '1')
		{
			set_directions(data);
			break ;
		}
		data->var.x_d += data->var.xinc;
		data->var.y_d += data->var.yinc;
	}
}
