/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:47:56 by nrontey           #+#    #+#             */
/*   Updated: 2024/11/30 12:45:41 by nrontey          ###   ########.fr       */
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

static void	free_text_tab(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->map->textures[i])
			mlx_destroy_image(data->mlx, data->map->textures[i]);
		i++;
	}
}

void	ft_free_data(t_data *data)
{
	free_text_tab(data);
	if (data->mlx)
	{
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
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
