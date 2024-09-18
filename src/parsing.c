/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:42:12 by nrontey           #+#    #+#             */
/*   Updated: 2024/09/18 10:17:48 by nrontey          ###   ########.fr       */
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

int		handle_texture_data(char *line, t_textures *textures)
{
	if (get_line_texture(line, textures))
		return (1);
	return (0);
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
        {
            free(line);
            return (0);
        }
        free(line);
        line = get_next_line_trim(fd);
    }
	free(line);
    return (1);
}

int		ft_get_content(int fd, t_data *data)
{
	int		n_line;

	n_line = 0;
	if (!ft_init_textures(data))
		return (0);
	if (!ft_parsing_texture(fd, data, &n_line))
		return (0);
	printf("NO: %s\n", data->textures->NO_file);
	printf("SO: %s\n", data->textures->SO_file);
	printf("WE: %s\n", data->textures->WE_file);
	printf("EA: %s\n", data->textures->EA_file);
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
	if (!ft_get_content(fd, data))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
