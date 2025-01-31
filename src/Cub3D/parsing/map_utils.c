/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:13:43 by nrontey           #+#    #+#             */
/*   Updated: 2025/01/31 01:11:02 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_set_max_space(t_map *map)
{
	char	**map_2d;
	int		max;
	int		i;
	char	*tmp;
	char	*new;

	i = 0;
	map_2d = map->map_2d;
	max = get_max_line(map_2d);
	while (map_2d[i])
	{
		tmp = map_2d[i];
		new = ft_calloc(max + 1, sizeof(char));
		ft_memset(new, ' ', max);
		ft_copy(tmp, new);
		free(tmp);
		map_2d[i] = new;
		i++;
	}
}

void	ft_fill_map(char *old_line, int fd, t_map *map)
{
	char	*line;
	int		i;
	char	*check;

	i = 0;
	line = old_line;
	while (line)
	{
		check = ft_strtrim(line, " t");
		if (!check || !ft_strlen(check))
		{
			free(check);
			break ;
		}
		map->map_2d[i++] = ft_strdup(line);
		free(line);
		free(check);
		line = get_next_line_trim(fd);
	}
	while (line)
	{
		free(line);
		line = get_next_line_trim(fd);
	}
	map->map_height = i;
}
