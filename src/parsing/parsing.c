/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:42:12 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 06:29:07 by nrontey          ###   ########.fr       */
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

static void	big_print(t_data *data)
{
	printf("Textures:\nNO: %s\nSO: %s\nWE: %s\nEA: %s\n", data->textures->NO_file, data->textures->SO_file, data->textures->WE_file, data->textures->EA_file);
	printf("Floor color: %d, %d, %d\n", data->textures->F_R, data->textures->F_G, data->textures->F_B);
	printf("Ceiling color: %d, %d, %d\n", data->textures->C_R, data->textures->C_G, data->textures->C_B);
	printf("Map:\n");
	for (int i = 0; i < data->map->map_height; i++)
		printf("%s|\n", data->map->map_2d[i]);
	if (data->map->is_player)
	{
		printf("Player position: %f, %f\n", data->map->player->current_position->x, data->map->player->current_position->y);
		printf("Player rotation: %f\n", data->map->player->rotation);
	}
	else
		printf("Error\nNo player position found\n");
}

static int	ft_check_map(t_data *data)
{
	if (!data->map->is_player)
	{
		printf("Error\nNo player position found\n");
		return (0);
	}
	if (!check_map_lines(data->map))
	{
		printf("Error\nInvalid map\n");
		return (0);
	}
	if (!check_map_content(data->map->map_2d))
	{
		printf("Error\nInvalid map\n");
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
		return (0);
	if (!ft_parsing_map(fd, data, &n_line))
		return (0);
	if (!ft_check_map(data))
		return (0);
	data->map->map_width = (int)get_max_line(data->map->map_2d);
	big_print(data);
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
	if ((!filename || ft_strlen(filename) < 4) || \
		(ft_strcmp(filename + ft_strlen(filename) - 4, ".cub")))
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
