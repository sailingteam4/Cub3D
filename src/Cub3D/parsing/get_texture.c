/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:02:17 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/12 20:37:05 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_line_texture(char *line, t_textures *textures)
{
	char	**line_tab;
	char	*element;

	line_tab = ft_split(line, ' ');
	if (!line_tab)
		return (0);
	if (!line_tab || !line_tab[0] || !line_tab[1] || ft_strlen(line_tab[0]) > 2)
		return (free_tab(line_tab));
	element = line_tab[0];
	if ((!ft_strcmp(element, "NO") || (ft_strlen(element) == 1 && \
			element[0] == 'N' )) && !textures->NO_file)
		textures->NO_file = ft_strdup(line_tab[1]);
	if ((!ft_strcmp(element, "SO") || (ft_strlen(element) == 1 && \
				element[0] == 'S')) && !textures->SO_file)
		textures->SO_file = ft_strdup(line_tab[1]);
	if ((!ft_strcmp(element, "WE") || (ft_strlen(element) == 1 && \
				element[0] == 'W')) && !textures->WE_file)
		textures->WE_file = ft_strdup(line_tab[1]);
	if ((!ft_strcmp(element, "EA") || (ft_strlen(element) == 1 && \
			element[0] == 'E')) && !textures->EA_file)
		textures->EA_file = ft_strdup(line_tab[1]);
	free_tab(line_tab);
	return (1);
}

int	handle_texture_data(char *line, t_textures *textures)
{
	if (get_line_texture(line, textures))
		return (1);
	return (0);
}

int	handle_color_data(char *line, t_textures *textures)
{
	char	**line_tab;

	line_tab = ft_split(line, ' ');
	if (!line_tab)
		return (0);
	if (!line_tab[0] || !line_tab[1])
		return (free_tab(line_tab));
	if ((!ft_strcmp(line_tab[0], "F") || !ft_strcmp(line_tab[0], "C")) \
		&& get_line_color(line_tab[1], line_tab[0][0], textures))
		return (free_tab(line_tab), 1);
	return (free_tab(line_tab), 0);
}

int	ft_parsing_texture(int fd, t_data *data, int *n_line)
{
	char	*line;

	line = get_next_line_trim(fd);
	if (!line)
		return (0);
	while (line)
	{
		(*n_line)++;
		if (ft_strlen(line) && ft_strchr("NSEW", line[0]) && \
			!handle_texture_data(line, data->textures))
			return (free(line), 1);
		else if (ft_strlen(line) && ft_strchr("FC", line[0]) && \
			!handle_color_data(line, data->textures))
			return (free(line), 1);
		free(line);
		if (is_valid_texture(data->textures))
			break ;
		line = get_next_line_trim(fd);
	}
	return (is_valid_texture(data->textures));
}
