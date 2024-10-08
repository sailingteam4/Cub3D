/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:42:12 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/08 05:11:54 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3D.h"

// int		count_lines(char *filename)
// {
// 	int		fd;
// 	int		lines;
// 	char	*line;

// 	lines = 0;
// 	fd = open(filename, O_RDsONLY);
// 	line = get_next_line(fd);
// 	if (!line)
// 	{
// 		close(fd);
// 		return (0);
// 	}
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		if (line)
// 			lines++;
// 	}
// 	close(fd);
// 	if (lines == 0 || lines < 9)
// 		return (0);
// 	return (lines);
// }

// char	**get_map(int ft_init_data)
// {
// 	char	**map;
// 	char	*line;
// 	int		fd;
// 	int		i;
// 	int		len;

// 	map = malloc(sizeof(char *) * (count_lines(filename) + 2));
// 	if (!map)
// 		return (NULL);
// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		len = ft_strlen(line) - 1;
// 		if (len > 0 && line[len] == '\n')
// 			line[len] = '\0';
// 		map[i] = line;
// 		i++;
// 		line = get_next_line(fd);
// 	}
// 	map[i] = NULL;
// 	close(fd);
// 	return (map);
// }

int		ft_init_textures(t_data *data)
{
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
		return (0);
	data->textures->NO_file = NULL;
	data->textures->SO_file = NULL;
	data->textures->WE_file = NULL;
	data->textures->EA_file = NULL;
	data->textures->F_ok = 0;
	data->textures->C_ok = 0;
	data->textures->F_R = -1;
	data->textures->F_G = -1;
	data->textures->F_B = -1;
	data->textures->C_R = -1;
	data->textures->C_G = -1;
	data->textures->C_B = -1;
	return (1);
}

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

int		free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

int		get_line_texture(char *line, t_textures *textures)
{
	char	**line_tab;
	char	*element;

	line_tab = ft_split(line, ' ');
	if (!line_tab)
		return (0);
	if (!line_tab || !line_tab[0] || !line_tab[1] || ft_strlen(line_tab[0]) > 2)
		return (free_tab(line_tab));
	element = line_tab[0];
	if (!ft_strcmp(element, "NO") || (ft_strlen(element) == 1 && element[0] == 'N' ))
		textures->NO_file = ft_strdup(line_tab[1]);
	if (!ft_strcmp(element, "SO") || (ft_strlen(element) == 1 && element[0] == 'S'))
		textures->SO_file = ft_strdup(line_tab[1]);
	if (!ft_strcmp(element, "WE") || (ft_strlen(element) == 1 && element[0] == 'W'))
		textures->WE_file = ft_strdup(line_tab[1]);
	if (!ft_strcmp(element, "EA") || (ft_strlen(element) == 1 && element[0] == 'E'))
		textures->EA_file = ft_strdup(line_tab[1]);
	free_tab(line_tab);
	return (1);
}

int		ft_isnumeric(char *str)
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

int		is_valid_color(char **colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!colors[i] || (i > 0 && !ft_isnumeric(colors[i])))
			return (0);
		i++;
	}
	return (1);
}

int		get_line_color(char *str, char mode, t_textures *textures)
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

int		handle_texture_data(char *line, t_textures *textures)
{
	if (get_line_texture(line, textures))
		return (1);
	return (0);
}

int		handle_color_data(char *line, t_textures *textures)
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

int		is_valid_texture(t_textures *textures)
{
	return (textures->NO_file && textures->SO_file && textures->WE_file && textures->EA_file && textures->F_ok && textures->C_ok);
}

int		ft_parsing_texture(int fd, t_data *data, int *n_line)
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

int		ft_init_map(t_data *data, int *n_line)
{
	char	**map;

	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		return (0);
	data->map->player = ft_calloc(1, sizeof(t_player));
	if (!data->map->player)
		return (0);
	data->map->player->current_position = NULL;
	data->map->player->start_position = NULL;
	data->map->map_height = data->n_line_file - *n_line;
	data->map->is_player = 0;
	map = ft_calloc(data->map->map_height + 1, sizeof(char *));
	data->map->map_2d = map;
	return (1);
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
			break ;
		map->map_2d[i++] = ft_strdup(line);
		free(line);
		free(check);
		line = get_next_line_trim(fd);
	}
	map->map_height = i;
}

int		ft_parsing_map(int fd, t_data *data, int *n_line)
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
		}
		(*n_line)++;
		line = get_next_line_trim(fd);
	}
	return (1);
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

int		ft_get_content(int fd, t_data *data, char *filename)
{
	int		n_line;

	n_line = 0;
	data->n_line_file = ft_get_nb_lines(filename);
	if (!ft_init_textures(data))
		return (0);
	if (!ft_parsing_texture(fd, data, &n_line))
		return (0);
	if (!ft_parsing_map(fd, data, &n_line))
		return (0);
	printf("Textures:\nNO: %s\nSO: %s\nWE: %s\nEA: %s\n", data->textures->NO_file, data->textures->SO_file, data->textures->WE_file, data->textures->EA_file);
	printf("Floor color: %d, %d, %d\n", data->textures->F_R, data->textures->F_G, data->textures->F_B);
	printf("Ceiling color: %d, %d, %d\n", data->textures->C_R, data->textures->C_G, data->textures->C_B);
	return (1);
}

int		ft_check_file(char *filename, int ac, t_data *data)
{
	int	fd;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (0);
	}
	if ((!filename || ft_strlen(filename) < 4) || (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub")))
	{
		printf("Error\nInvalid file name or extension\n");
		return (0);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open file\n");
		return (0);
	}
	if (!ft_get_content(fd, data, filename))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
