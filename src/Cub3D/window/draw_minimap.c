/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:02:59 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/24 06:09:32 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_minimap_tile(t_data *data, int x, int y, int size_modifier)
{
	int	color;
	int	i;
	int	j;
	float player_x = data->map->player->current_position->y;
	float player_y = data->map->player->current_position->x;

	if (data->map->map_2d[y][x] == '1')
	{
		color = mlx_rgb_to_int(0, 255, 255, 255);
		i = 0;
		while (i < size_modifier)
		{
			j = 0;
			while (j < size_modifier)
			{
				mlx_draw_pixel(data->img, x * size_modifier + i, 
					y * size_modifier + j, color);
				j++;
			}
			i++;
		}
	}
	else
	{
		color = mlx_rgb_to_int(0, 100, 0, 0);
		i = 0;
		while (i < size_modifier)
		{
			j = 0;
			while (j < size_modifier)
			{
				mlx_draw_pixel(data->img, x * size_modifier + i, 
					y * size_modifier + j, color);
				j++;
			}
			i++;
		}
	}

	if (x == (int)player_x && y == (int)player_y)
	{
		int player_size = size_modifier / 3;
		color = mlx_rgb_to_int(0, 0, 255, 0);
		
		float precise_x = (player_x - (int)player_x) * size_modifier;
		float precise_y = (player_y - (int)player_y) * size_modifier;

		i = -player_size/2;
		while (i < player_size/2)
		{
			j = -player_size/2;
			while (j < player_size/2)
			{
				mlx_draw_pixel(data->img, 
					x * size_modifier + precise_x + i, 
					y * size_modifier + precise_y + j, 
					color);
				j++;
			}
			i++;
		}

		color = mlx_rgb_to_int(0, 255, 255, 0);
		float dir_x = cos(data->map->player->rotation) * size_modifier;
		float dir_y = sin(data->map->player->rotation) * size_modifier;
		int line_length = size_modifier;
		
		i = 0;
		while (i < line_length)
		{
			mlx_draw_pixel(data->img,
				x * size_modifier + precise_x + (dir_x * i / line_length),
				y * size_modifier + precise_y + (dir_y * i / line_length),
				color);
			i++;
		}
	}
}

int	put_minimap(t_data *data, int size_modifier)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map->map_height)
	{
		x = 0;
		while (x < data->map->map_width)
		{
			draw_minimap_tile(data, x, y, size_modifier);
			x++;
		}
		y++; 
	}
	return (1);
}

int	update_minimap(t_data *data, int size_modifier)
{
	if (data->map->minimap_display)
	{
		put_minimap(data, size_modifier);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
		return (1);
	}
	mlx_clear_window(data->mlx, data->mlx_win);
	return (0);
}
