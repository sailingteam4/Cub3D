/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:58:24 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/03 16:05:05 by nrontey          ###   ########.fr       */
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
	int		last_wall;

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
		if (ft_strlen(trimmed_line) && trimmed_line[0] != '1')
			return (free(trimmed_line), 0);
		last_wall = ft_strlen(trimmed_line) - 1;
		while (last_wall >= 0 && trimmed_line[last_wall] == '0')
			last_wall--;
		if (last_wall >= 0 && trimmed_line[last_wall] != '1')
			return (free(trimmed_line), 0);
		free(trimmed_line);
	}
	return (1);
}

int	check_walls_space(char **map, int x, int y)
{
	if (!map[x] || !map[x][y])
		return (0);
	if (x == 0 || (!map[x - 1][y] || (map[x - 1][y] \
			!= '1' && map[x - 1][y] != '0')))
		return (0);
	if (!map[x + 1] || (!map[x + 1][y] || (map[x + 1][y] \
			!= '1' && map[x + 1][y] != '0')))
		return (0);
	if (y == 0 || (!map[x][y - 1] || (map[x][y - 1] \
			!= '1' && map[x][y - 1] != '0')))
		return (0);
	if (!map[x][y + 1] || (map[x][y + 1] \
			!= '1' && map[x][y + 1] != '0'))
		return (0);
	return (1);
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
			if (map[x][y] == '0' || ft_is_player_char(map[x][y]))
			{
				if (!check_walls_space(map, x, y))
					return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}
