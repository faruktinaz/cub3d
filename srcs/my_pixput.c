/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 00:18:04 by ogenc             #+#    #+#             */
/*   Updated: 2024/01/19 02:13:23 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	img_pix_put(t_image *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->data + (y * image->sizeline + x * (image->bpp / 8));
	*(int *)pixel = color;
}

unsigned int	get_pixel_in_texture(t_texture *texture, int x, int y)
{
	char	*re;

	re = texture->data + (y * texture->sizeline + x * (texture->bpp / 8));
	return (*((unsigned int *)re));
}
