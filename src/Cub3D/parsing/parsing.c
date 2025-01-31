/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:42:12 by nrontey           #+#    #+#             */
/*   Updated: 2025/01/31 01:11:02 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	ft_parsing_map(int fd, t_data *data, int *n_line)
{
	char	*line;

	line = get_next_line_trim(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (!ft_strlen(line))
			free(line);
		else
		{
			if (!ft_init_map(data, n_line))
				return (0);
			ft_fill_map(line, fd, data->map);
			get_player(data);
			ft_set_max_space(data->map);
			return (1);
		}
		(*n_line)++;
		line = get_next_line_trim(fd);
	}
	return (1);
}

static int	ft_check_map(t_data *data)
{
	if (data->map)
	{
		if (!data->map->is_player)
		{
			printf("Error\nNo player position found\n");
			return (0);
		}
		if (!check_map_lines(data->map))
		{
			printf("Error\nInvalid character\n");
			return (0);
		}
		if (!check_map_content(data->map->map_2d))
		{
			printf("Error\nInvalid map\n");
			return (0);
		}
	}
	else
	{
		printf("Error\nNo map found\n");
		return (0);
	}
	return (1);
}

static int	ft_get_content(int fd, t_data *data, char *filename)
{
	int		n_line;

	if (fd < 0)
	{
		printf("Error\nCould not open file\n");
		return (0);
	}
	n_line = 0;
	data->n_line_file = ft_get_nb_lines(filename);
	if (!ft_init_textures(data))
		return (0);
	if (!ft_parsing_texture(fd, data, &n_line))
	{
		printf("Error\nInvalid texture\n");
		return (0);
	}
	if (!ft_parsing_map(fd, data, &n_line))
	{
		printf("Map skill issue\n");
		return (0);
	}
	if (!ft_check_map(data))
		return (0);
	data->map->map_width = (int)get_max_line(data->map->map_2d);
	return (1);
}

int	ft_check_file(char *filename, int ac, t_data *data)
{
	int	fd;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (0);
	}
	if (!is_valid_ext(filename, ".cub"))
	{
		printf("Error\nInvalid file name or extension\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (!ft_get_content(fd, data, filename))
	{
		if (fd > 0)
			close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
