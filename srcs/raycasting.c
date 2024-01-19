/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:21:49 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/19 02:18:16 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	draw3d_view_wallsize(t_data *data, int walltstart, int walltend, int i)
{
	data->var.k = walltstart * 0.0016685 * (data->window_width);
	while (data->var.k <= walltend * 0.0016685 * (data->window_width))
	{
		if (data->end_j >= data->window_height)
			break ;
		data->var.walltes = (data->end_j - data->start) * 64.0 / data->height;
		data->var.wall_x = data->wall_x[i] - floor(data->wall_x[i]);
		data->var.wall_y = data->wall_y[i] - floor(data->wall_y[i]);
		data->var.wallcolor = get_pixel_in_texture(&data->textures[0] \
			, (data->var.wall_x) * 64, data->var.walltes);
		check_wall_dir(data, i);
		set_raycasting_dir(data, &i);
		data->var.k++;
	}
}

void	check_wall_dir(t_data *data, int i)
{
	if (data->wall_direction[i] == 0)
	{
		if (data->wall_direction[i - 1])
			data->wall_direction[i] = data->wall_direction[i - 1];
		else if (data->wall_direction[i + 1])
			data->wall_direction[i] = data->wall_direction[i + 1];
	}
}

void	put_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->window_height / 2)
	{
		x = 0;
		while (x < data->window_width)
		{
			img_pix_put(&data->image, x, y, data->skyc);
			x++;
		}
		y++;
	}
	while (y < data->window_height)
	{
		x = 0;
		while (x < data->window_width)
		{
			img_pix_put(&data->image, x, y, data->floorc);
			x++;
		}
		y++;
	}
}

void	draw3d_view(t_data *data, int numRays)
{
	int	walltstart;
	int	walltend;
	int	i;

	i = 0;
	while (i < numRays)
	{
		walltstart = i - (1 / data->distances[i]);
		walltend = i + (1 / data->distances[i]);
		data->height = (data->window_height * 30 / data->distances[i]);
		data->start = (data->window_height / 2) - (data->height / 2);
		data->end = (data->window_height / 2) + (data->height / 2);
		if (data->start < 0)
			data->end_j = 0;
		else
			data->end_j = data->start;
		while (data->end_j < data->end)
		{
			draw3d_view_wallsize(data, walltstart, walltend, i);
			data->end_j++;
		}
		i++;
	}
}

int	raycasting(t_data *data)
{
	float	i;
	float	end_x;
	float	end_y;

	data->jd = 0;
	i = -30;
	mlx_clear_window(data->mlx, data->mlx_win);
	while (i <= 30)
	{
		data->current_angle = data->var.pa + (i * DR);
		end_x = data->p_x - 12 + cos(data->current_angle) * 1024;
		end_y = data->p_y - 12 + sin(data->current_angle) * 1024;
		dda((int)end_x, (int)end_y, data);
		i += 0.1;
	}
	put_background(data);
	draw3d_view(data, 600);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->image.window, 0, 0);
	return (0);
}
