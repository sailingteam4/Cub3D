/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:49:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/14 15:46:22 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	make_the_window(t_data *data)
{
	(void)data;
	return (1);
}

int	is_color_ok(t_textures *textures)
{
	return (textures->F_R == -1 || textures->F_G == -1 || textures->F_B == -1
		|| textures->C_R == -1 || textures->C_G == -1 || textures->C_B == -1);
}

int	is_texture_ok(t_textures *textures)
{
	int		*temp_fd;
	int		i;

	temp_fd = malloc(sizeof(int) * 4);
	if (!temp_fd)
		return (1);
	temp_fd[0] = open(textures->NO_file, O_RDONLY);
	temp_fd[1] = open(textures->SO_file, O_RDONLY);
	temp_fd[2] = open(textures->WE_file, O_RDONLY);
	temp_fd[3] = open(textures->EA_file, O_RDONLY);
	i = 0;
	while (i < 4)
	{
		if (temp_fd[i] == -1)
		{
			free(temp_fd);
			return (1);
		}
		close(temp_fd[i]);
		i++;
	}
	free(temp_fd);
	return (0);
}

int	ft_check_map(t_data *data)
{
	if (data->map->player->player_count != 1)
	{
		printf("Error\nThere should be only one player\n");
		return (0);
	}
	if (is_color_ok(data->textures))
	{
		printf("Error\nProblem with color\n");
		return (0);
	}
	if (is_texture_ok(data->textures))
	{
		printf("Error\nProblem with texture\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_init_data(data);
	if (!ft_check_file(av[1], ac, data))
	{
		ft_free_data(data);
		return (1);
	}
	if (!ft_check_map(data))
	{
		ft_free_data(data);
		return (1);
	}
	if (!make_the_window(data))
	{
		ft_free_data(data);
		return (1);
	}
	ft_free_data(data);
	return (0);
}
