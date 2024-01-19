/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaz <tinaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:33:53 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/19 23:48:49 by tinaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	abs(int n)
{
	if (n < 0)
		return (n * (-1));
	else
		return (n);
}

void	ft_init(t_data *data)
{
	data->map_cub = NULL;
	data->distances = malloc(sizeof(float) * 600);
	data->wall_direction = malloc(sizeof(int) * 600);
	data->window_width = 1024;
	data->window_height = 1024;
	data->wall_x = calloc(sizeof(float), 600);
	data->wall_y = calloc(sizeof(float), 600);
	data->attr = ft_calloc(sizeof(t_attr), 1);
	data->pl_a = 0;
	data->mlx = mlx_init();
	data->current_angle = 0.0;
	data->mlx_win = mlx_new_window(data->mlx, data->window_width,
			data->window_height, "cub3d");
}

void	create_rgb(char *line, enum e_map type, t_data *data)
{
	int	color[3];
	int	i;
	int	j;
	int	result;

	i = -1;
	result = 0;
	j = 0;
	while (line[++i])
	{
		while (line[i] && ft_isdigit(line[i]))
		{
			result = (result * 10) + (line[i] - '0');
			i++;
		}
		color[j] = result;
		result = 0;
		if ((j++) == 2)
			break ;
	}
	num_limit_check(color);
	if (type == CEILING)
		data->skyc = color[0] << 16 | color[1] << 8 | color[2];
	else if (type == FLOOR)
		data->floorc = color[0] << 16 | color[1] << 8 | color[2];
}

void	dda(int x1, int y1, t_data *data)
{
	data->var.dx = x1 - (data->p_x - 12);
	data->var.dy = y1 - (data->p_y - 12);
	if (abs(data->var.dx) > abs(data->var.dy))
		data->var.steps = abs(data->var.dx);
	else
		data->var.steps = abs(data->var.dy);
	data->var.xinc = data->var.dx / (float)data->var.steps;
	data->var.yinc = data->var.dy / (float)data->var.steps;
	data->direction = 0;
	data->var.x_d = (data->p_x - 12) + 20;
	data->var.y_d = (data->p_y - 12) + 20;
	ray_sending(data);
	data->distances[data->jd] = (sqrt(pow(data->p_x + 8 - data->var.x_d, 2) + \
		pow(data->p_y + 8 - data->var.y_d, 2)) \
		* cos(data->current_angle - data->var.pa));
	data->wall_direction[data->jd] = data->direction;
	data->wall_x[data->jd] = (data->var.x_d / 64);
	data->wall_y[data->jd] = (data->var.y_d / 64);
	data->jd++;
}
