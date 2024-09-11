/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:42:12 by nrontey           #+#    #+#             */
/*   Updated: 2024/09/11 02:08:17 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3D.h"

int		count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			lines++;
	}
	close(fd);
	if (lines == 0 || lines < 9)
		return (0);
	return (lines);
}

char	**get_map(char *filename)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;
	int		len;

	map = malloc(sizeof(char *) * (count_lines(filename) + 2));
	if (!map)
		return (NULL);
	i = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line) - 1;
		if (len > 0 && line[len] == '\n')
			line[len] = '\0';
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	ft_map_parsing(char *filename, t_map *map)
{
	char	**map_char;

	map_char = get_map(filename);
	if (!map_char)
		return ;
	(void)map;
}

int		ft_check_file(char *filename, int ac)
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
	close(fd);
	return (1);
}
