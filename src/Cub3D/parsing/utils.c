/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:24:03 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/12 20:37:24 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_copy(char *src, char *dst)
{
	while (src && *src)
		*dst++ = *src++;
}

int	is_valid_ext(char *filename, char *ext)
{
	if ((!filename || ft_strlen(filename) < 4) || \
		(ft_strcmp(filename + ft_strlen(filename) - 4, ext)))
		return (0);
	return (1);
}
