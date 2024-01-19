/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaz <tinaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 23:57:35 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/20 00:10:31 by tinaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(0);
}

char	*find_direction(t_data *data, int type)
{
	t_map	*temp;

	temp = data->attr->texture;
	while (temp)
	{
		if (temp->type == type)
			return (temp->line);
		temp = temp->next;
	}
	ft_error();
	return (NULL);
}

void	draw_utils2(t_data *data)
{
	if (!data->textures[0].image || !data->textures[1].image \
		|| !data->textures[2].image || !data->textures[3].image)
		ft_error();
	data->textures[2].data = mlx_get_data_addr(data->textures[2].image, \
		&data->textures[2].bpp, &data->textures[2].sizeline, \
		&data->textures[2].endian);
	data->textures[3].data = mlx_get_data_addr(data->textures[3].image, \
	&data->textures[3].bpp, &data->textures[3].sizeline, \
	&data->textures[3].endian);
	data->textures[0].data = mlx_get_data_addr(data->textures[0].image, \
		&data->textures[0].bpp, &data->textures[0].sizeline, \
		&data->textures[0].endian);
	data->textures[1].data = mlx_get_data_addr(data->textures[1].image, \
		&data->textures[1].bpp, &data->textures[1].sizeline, \
		&data->textures[1].endian);
}

void	draw_utils(t_data *data)
{
	int		w;
	t_map	*color_temp;

	w = 0;
	color_temp = data->attr->color;
	data->image.window = mlx_new_image(data->mlx,
			data->window_width, data->window_height);
	data->image.data = mlx_get_data_addr(data->image.window, &data->image.bpp, \
		&data->image.sizeline, &data->image.endian);
	data->textures[0].image = mlx_xpm_file_to_image(data->mlx, \
		find_direction(data, EAST), &w, &w);
	data->textures[2].image = mlx_xpm_file_to_image(data->mlx, \
		find_direction(data, NORTH), &w, &w);
	data->textures[3].image = mlx_xpm_file_to_image(data->mlx, \
		find_direction(data, SOUTH), &w, &w);
	data->textures[1].image = mlx_xpm_file_to_image(data->mlx, \
		find_direction(data, WEST), &w, &w);
	draw_utils2(data);
	while (color_temp)
	{
		create_rgb(color_temp->line, color_temp->type, data);
		color_temp = color_temp->next;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		ft_error();
	data = malloc(sizeof(t_data));
	ft_init(data);
	data->map_arg = av[1];
	ft_parse(data);
	draw_utils(data);
	set_player_angle(data);
	data->var.pdx = cos(data->var.pa) * 5;
	data->var.pdy = sin(data->var.pa) * 5;
	raycasting(data);
	mlx_hook(data->mlx_win, 17, 0, x_button, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, &key_event, data);
	mlx_loop(data->mlx);
}
