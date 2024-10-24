/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:06:57 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 06:21:41 by nrontey          ###   ########.fr       */
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
		textures->F_R = ft_atoi(colors[0]);
		textures->F_G = ft_atoi(colors[1]);
		textures->F_B = ft_atoi(colors[2]);
		textures->F_ok = 1;
		return (free_tab(colors), 1);
	}
	else if (mode == 'C')
	{
		textures->C_R = ft_atoi(colors[0]);
		textures->C_G = ft_atoi(colors[1]);
		textures->C_B = ft_atoi(colors[2]);
		textures->C_ok = 1;
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
