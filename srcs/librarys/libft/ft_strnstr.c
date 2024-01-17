/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:06 by ogenc             #+#    #+#             */
/*   Updated: 2023/11/17 04:20:12 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)str);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while ((i + j) < len && str[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *) &str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
