/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 04:57:28 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/24 06:10:51 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	exit_mlx(t_data *data)
{
	ft_free_data(data);
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit_mlx(data);
	if (keycode == 119)
	{
		data->map->player->current_position->x -= 1;
		update_minimap(data, HEIGHT / 80);
	}
	if (keycode == 115)
	{
		data->map->player->current_position->x += 1;
		update_minimap(data, HEIGHT / 80);
	}
	if (keycode == 97)
	{
		data->map->player->current_position->y -= 1;
		update_minimap(data, HEIGHT / 80);
	}
	if (keycode == 100)
	{
		data->map->player->current_position->y += 1;
		update_minimap(data, HEIGHT / 80);
	}
	if (keycode == 109)
	{
		data->map->minimap_display = !data->map->minimap_display;
		update_minimap(data, HEIGHT / 80);
	}
	return (0);
}

int	close_win(t_data *data)
{
	exit_mlx(data);
	return (0);
}
