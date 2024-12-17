/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:44:50 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/17 11:28:50 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_init_textures(t_data *data)
{
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
		return (0);
	data->textures->no_file = NULL;
	data->textures->so_file = NULL;
	data->textures->we_file = NULL;
	data->textures->ea_file = NULL;
	data->textures->f_ok = 0;
	data->textures->c_ok = 0;
	data->textures->f_r = -1;
	data->textures->f_g = -1;
	data->textures->f_b = -1;
	data->textures->c_r = -1;
	data->textures->c_g = -1;
	data->textures->c_b = -1;
	return (1);
}

void	ft_init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map = NULL;
	data->textures = NULL;
}

int	ft_init_map(t_data *data, int *n_line)
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
	data->map->player->moving_forward = 0;
	data->map->player->moving_backward = 0;
	data->map->player->moving_left = 0;
	data->map->player->moving_right = 0;
	data->map->player->rotating_left = 0;
	data->map->player->rotating_right = 0;
	data->map->map_height = data->n_line_file - *n_line;
	data->map->is_player = 0;
	data->map->minimap_display = true;
	map = ft_calloc(data->map->map_height + 1, sizeof(char *));
	data->map->map_2d = map;
	return (1);
}
