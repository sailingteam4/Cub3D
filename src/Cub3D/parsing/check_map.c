/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:58:24 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 06:18:56 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_check_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_valid_chars(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_map_lines(t_map *map)
{
	char	*line;
	char	*trimmed_line;
	int		i;

	i = 0;
	line = map->map_2d[i];
	while (line)
	{
		line = map->map_2d[i++];
		trimmed_line = ft_strtrim(line, " \t\n");
		if (!trimmed_line || !ft_strlen(trimmed_line))
			break ;
		else if (ft_check_chars(trimmed_line))
			return (free(trimmed_line), 0);
		if (ft_strlen(trimmed_line) && \
			(trimmed_line[0] != '1' || \
				trimmed_line[ft_strlen(trimmed_line) - 1] != '1'))
			return (free(trimmed_line), 0);
		free(trimmed_line);
	}
	return (1);
}

int	check_walls_space(char **map, int x, int y)
{
	if (map[x] && map[x][y])
	{
		if ((x > 0 && !is_char_valid_walls_space(map[x - 1][y]))
		|| (map[x + 1] && !is_char_valid_walls_space(map[x + 1][y]))
		|| !map[x + 1])
			return (0);
		else if ((y > 0 && !is_char_valid_walls_space(map[x][y - 1]))
		|| !is_char_valid_walls_space(map[x][y + 1]))
			return (0);
		return (1);
	}
	return (0);
}

int	check_map_content(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0')
				if (check_walls_space(map, x, y))
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}
