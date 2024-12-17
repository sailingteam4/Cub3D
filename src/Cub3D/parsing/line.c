/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:06:57 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/17 11:28:50 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*get_next_line_trim(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	trimmed = ft_strtrim(line, " \n");
	free(line);
	return (trimmed);
}

int	get_line_color(char *str, char mode, t_textures *textures)
{
	char	**colors;

	colors = ft_split(str, ',');
	if (!colors)
		return (0);
	if (!is_valid_color(colors) || colors[3])
		return (free_tab(colors));
	if (mode == 'F')
	{
		textures->f_r = ft_atoi(colors[0]);
		textures->f_g = ft_atoi(colors[1]);
		textures->f_b = ft_atoi(colors[2]);
		textures->f_ok = 1;
		return (free_tab(colors), 1);
	}
	else if (mode == 'C')
	{
		textures->c_r = ft_atoi(colors[0]);
		textures->c_g = ft_atoi(colors[1]);
		textures->c_b = ft_atoi(colors[2]);
		textures->c_ok = 1;
		return (free_tab(colors), 1);
	}
	return (free_tab(colors), 0);
}

size_t	get_max_line(char **map)
{
	size_t	max;
	int		i;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

int	ft_get_nb_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}
