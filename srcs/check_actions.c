/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:11:29 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/19 07:02:41 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	check_action_a(t_data *data, float t_pdy, float t_pdx)
{
	if (data->attr->arr_map[(int)((data->p_y - 12) - t_pdy + 20) / 64]
		[(int)((data->p_x - 12) - t_pdx + 20) / 64] != '\n' &&
		data->attr->arr_map[(int)((data->p_y - 12) - t_pdy + 20) / 64]
		[(int)((data->p_x - 12) - t_pdx + 20) / 64] != '1' &&
		data->attr->arr_map[(int)((data->p_y - 12) - t_pdy + 20) / 64]
			[(int)((data->p_x - 12) - t_pdx + 20) / 64] != ' ')
		return (1);
	return (0);
}

int	check_action_d(t_data *data, float t_pdy, float t_pdx)
{
	if (data->attr->arr_map[(int)((data->p_y - 12) + t_pdy + 20) / 64]
		[(int)((data->p_x - 12) + t_pdx + 20) / 64] != '\n' &&
		data->attr->arr_map[(int)((data->p_y - 12) + t_pdy + 20) / 64]
		[(int)((data->p_x - 12) + t_pdx + 20) / 64] != '1' &&
		data->attr->arr_map[(int)((data->p_y - 12) + t_pdy + 20) / 64]
			[(int)((data->p_x - 12) + t_pdx + 20) / 64] != ' ')
		return (1);
	return (0);
}

int	check_action_w(t_data *data)
{
	if (data->attr->arr_map[(int)((data->p_y - 12) + data->var.pdy + 20) / 64]
		[(int)((data->p_x - 12) + data->var.pdx + 20) / 64] != '\n' &&
		data->attr->arr_map[(int)((data->p_y - 12) + data->var.pdy + 20) / 64]
		[(int)((data->p_x - 12) + data->var.pdx + 20) / 64] != '1' &&
		data->attr->arr_map[(int)((data->p_y - 12) + data->var.pdy + 20) / 64]
			[(int)((data->p_x - 12) + data->var.pdx + 20) / 64] != ' ')
		return (1);
	return (0);
}

int	check_action_s(t_data *data)
{
	if (data->attr->arr_map
		[(int)((data->p_y - 12) - data->var.pdy + 20) / 64] \
		[(int)((data->p_x - 12) - data->var.pdx + 20) / 64] != '\n' &&
		data->attr->arr_map
		[(int)((data->p_y - 12) - data->var.pdy + 20) / 64] \
		[(int)((data->p_x - 12) - data->var.pdx + 20) / 64] != '1' && \
		data->attr->arr_map[(int)((data->p_y - 12) - data->var.pdy + 20) / 64]
			[(int)((data->p_x - 12) - data->var.pdx + 20) / 64] != ' ')
		return (1);
	return (0);
}

int	x_button(t_data *data)
{
	(void)data;
	printf("*-*-* exit *-*-*\n");
	mlx_destroy_image(data->mlx, data->image.window);
	mlx_destroy_image(data->mlx, data->textures[0].image);
	mlx_destroy_image(data->mlx, data->textures[1].image);
	mlx_destroy_image(data->mlx, data->textures[2].image);
	mlx_destroy_image(data->mlx, data->textures[3].image);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}
