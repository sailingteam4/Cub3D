/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:47:56 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 06:19:22 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	free_tab(char **tab)
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

static void	ft_free_texture(t_textures *textures)
{
	if (textures->NO_file)
		free(textures->NO_file);
	if (textures->SO_file)
		free(textures->SO_file);
	if (textures->WE_file)
		free(textures->WE_file);
	if (textures->EA_file)
		free(textures->EA_file);
	free(textures);
}

static void	ft_free_player(t_player *player)
{
	if (player->current_position)
		free(player->current_position);
	if (player->start_position)
		free(player->start_position);
	free(player);
}

void	ft_free_data(t_data *data)
{
	if (data->mlx)
	{
		if (data->mlx_win)
			mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->textures)
		ft_free_texture(data->textures);
	if (data->map)
	{
		if (data->map->player)
			ft_free_player(data->map->player);
		if (data->map->map_2d)
			free_tab(data->map->map_2d);
		free(data->map);
	}
	free(data);
}
