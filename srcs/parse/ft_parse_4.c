/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 03:28:19 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/20 14:21:47 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_with_color2(char *line, int *check, int *rule, bool *flag)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (*(line + 1) != ' ')
			*flag = true;
		*check = 1;
		*rule += 1;
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (*(line + 1) != ' ')
			*flag = true;
		*check = 1;
		*rule += 1;
	}
	if (*check == 0)
		*flag = true;
}

void	parse_with_color3(char *line, int *digit_check, bool *flag, int *i)
{
	int	comma;
	int	check;

	check = 0;
	comma = 2;
	while (line[(*i)])
	{
		while (comma == 0 && line[(*i)] == ' ')
			i++;
		if (!(ft_isdigit(line[(*i)]) || line[(*i)] == ' ' \
			|| line[(*i)] == ',') && comma != 0)
			*flag = true;
		if (ft_isdigit(line[(*i)]))
			check += 1;
		if (comma == 0 && !(ft_isdigit(line[(*i)]) || line[(*i)] == '\n'))
			*flag = true;
		if (line[(*i)] == ',' || line[(*i)] == '\n')
		{
			if (check >= 1)
				(*digit_check) += 1;
			comma--;
			check = 0;
		}
		(*i)++;
	}
}
