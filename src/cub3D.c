/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:49:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 05:17:17 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		free_tab(char **tab);

static void	ft_init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map = NULL;
	data->textures = NULL;
}

static void	ft_free_data(t_data *data)
{
	if (data->mlx)
	{
		if (data->mlx_win)
			mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->textures)
	{
		if (data->textures->NO_file)
			free(data->textures->NO_file);
		if (data->textures->SO_file)
			free(data->textures->SO_file);
		if (data->textures->WE_file)
			free(data->textures->WE_file);
		if (data->textures->EA_file)
			free(data->textures->EA_file);
		free(data->textures);
	}
	if (data->map)
	{
		if (data->map->player)
		{
			if (data->map->player->current_position)
				free(data->map->player->current_position);
			if (data->map->player->start_position)
				free(data->map->player->start_position);
			free(data->map->player);
		}
		if (data->map->map_2d)
			free_tab(data->map->map_2d);
		free(data->map);
	}
	free(data);
}

int	make_the_window(t_data *data)
{
	(void)data;
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
	if (!make_the_window(data))
	{
		ft_free_data(data);
		return (1);
	}
	ft_free_data(data);
	return (0);
}
