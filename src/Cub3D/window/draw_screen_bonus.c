/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:02:59 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/11 22:12:41 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	draw_tile_border(t_data *data, int x, int y, \
		int size_modifier)
{
	int	i;
	int	j;
	int	border_size;

	i = 0;
	border_size = 1;
	while (i < size_modifier)
	{
		j = 0;
		while (j < size_modifier)
		{
			if (i < border_size || i >= size_modifier - border_size || \
				j < border_size || j >= size_modifier - border_size)
				mlx_draw_pixel(data->img, x * size_modifier + i,
					y * size_modifier + j, mlx_rgb_to_int(0, 40, 40, 40));
			j++;
		}
		i++;
	}
}

static void	draw_tile_content(t_data *data, int x, int y, int size_modifier)
{
	int	color;
	int	i;
	int	j;

	i = 1;
	while (i < size_modifier - 1)
	{
		j = 1;
		while (j < size_modifier - 1)
		{
			if (data->map->map_2d[y][x] == '1')
				color = mlx_rgb_to_int(0, 70, 130, 180);
			else
				color = mlx_rgb_to_int(0, 47, 79, 79);
			mlx_draw_pixel(data->img, x * size_modifier + i,
				y * size_modifier + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_tile(t_data *data, int x, int y, int size_modifier)
{
	draw_tile_border(data, x, y, size_modifier);
	draw_tile_content(data, x, y, size_modifier);
	if (x == (int)data->map->player->current_position->y && \
		y == (int)data->map->player->current_position->x)
		draw_player(data, x, y, size_modifier);
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

void	render_3d_view(t_data *data);

int	update_minimap(t_data *data, int size_modifier)
{
	render_3d_view(data);
	if (data->map->minimap_display)
	{
		put_minimap(data, size_modifier);
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (1);
}
