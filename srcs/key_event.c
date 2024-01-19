/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinaz <tinaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:09:08 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/20 00:05:35 by tinaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	check_keyevent_lr(t_data *data, int keycode)
{
	float	t_pdy;
	float	t_pdx;

	if (keycode == A)
	{
		t_pdy = cos(data->var.pa) * 5;
		t_pdx = -sin(data->var.pa) * 5;
		if (check_action_a(data, t_pdy, t_pdx))
		{
			data->p_y -= t_pdy;
			data->p_x -= t_pdx;
		}
	}
	else if (keycode == D)
	{
		t_pdy = cos(data->var.pa) * 5;
		t_pdx = -sin(data->var.pa) * 5;
		if (check_action_d(data, t_pdy, t_pdx))
		{
			data->p_y += t_pdy;
			data->p_x += t_pdx;
		}
	}
}

void	check_keyevent_ud(t_data *data, int keycode)
{
	if (keycode == W)
	{
		if (check_action_w(data))
		{
			data->p_y += data->var.pdy;
			data->p_x += data->var.pdx;
		}
	}
	else if (keycode == S)
	{
		if (check_action_s(data))
		{
			data->p_y -= data->var.pdy;
			data->p_x -= data->var.pdx;
		}
	}
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == LEFT_ARROW)
	{
		data->var.pa -= 0.1;
		if (data->var.pa < 0)
			data->var.pa += 2 * PI;
		data->var.pdx = cos(data->var.pa) * 5;
		data->var.pdy = sin(data->var.pa) * 5;
	}
	else if (keycode == RIGHT_ARROW)
	{
		data->var.pa += 0.1;
		if (data->var.pa > 2 * PI)
			data->var.pa -= 2 * PI;
		data->var.pdx = cos(data->var.pa) * 5;
		data->var.pdy = sin(data->var.pa) * 5;
	}
	else if (keycode == W || keycode == S)
		check_keyevent_ud(data, keycode);
	else if (keycode == A || keycode == D)
		check_keyevent_lr(data, keycode);
	else if (keycode == ESC)
		ft_exit("*-*-* Exit *-*-*");
	raycasting(data);
	return (0);
}
