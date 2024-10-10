/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:44:50 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 06:21:04 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_init_textures(t_data *data)
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
	data->map->map_height = data->n_line_file - *n_line;
	data->map->is_player = 0;
	map = ft_calloc(data->map->map_height + 1, sizeof(char *));
	data->map->map_2d = map;
	return (1);
}
