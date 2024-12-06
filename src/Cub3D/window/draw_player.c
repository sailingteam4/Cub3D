/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:11:17 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/05 19:11:27 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_player_glow(t_data *data, float px, float py, int radius)
{
	int	i;
	int	j;
	int	glow_color;

	glow_color = mlx_rgb_to_int(0, 255 - (radius * 30), \
		215 - (radius * 25), 0);
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= radius * radius)
				mlx_draw_pixel(data->img, px + i, py + j, glow_color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data, int x, int y, int size_modifier)
{
	float	precise_x;
	float	precise_y;
	int		player_size;
	int		radius;

	player_size = size_modifier / 2;
	precise_x = x * size_modifier + (data->map->player->current_position->y - \
		(int)data->map->player->current_position->y) * size_modifier;
	precise_y = y * size_modifier + (data->map->player->current_position->x - \
		(int)data->map->player->current_position->x) * size_modifier;
	radius = player_size / 2;
	while (radius >= 0)
	{
		draw_player_glow(data, precise_x, precise_y, radius);
		radius--;
	}
}
