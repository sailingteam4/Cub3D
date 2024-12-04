/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:02:59 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/04 17:43:43 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float	get_distance_to_wall(t_data *data, float x, float y, float angle)
{
	float	ray_x;
	float	ray_y;
	float	dir_x;
	float	dir_y;
	float	step;

	ray_x = x;
	ray_y = y;
	dir_x = cos(-angle);
	dir_y = sin(-angle);
	step = 0.01;
	while (ray_x >= 0 && ray_x < data->map->map_width && \
			ray_y >= 0 && ray_y < data->map->map_height && \
			data->map->map_2d[(int)ray_y][(int)ray_x] != '1')
	{
		ray_x += dir_x * step;
		ray_y += dir_y * step;
	}
	return (sqrt((ray_x - x) * (ray_x - x) + (ray_y - y) * (ray_y - y)));
}

static void	draw_tile_border(t_data *data, int x, int y, \
		int size_modifier, int border_size)
{
	int	i;
	int	j;

	i = 0;
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

static void	draw_player_glow(t_data *data, float px, float py, int radius)
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

static void	draw_player(t_data *data, int x, int y, int size_modifier)
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

void	draw_minimap_tile(t_data *data, int x, int y, int size_modifier)
{
	draw_tile_border(data, x, y, size_modifier, 1);
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
	mlx_clear_window(data->mlx, data->mlx_win);
	render_3d_view(data);
	if (data->map->minimap_display)
	{
		put_minimap(data, size_modifier);
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (1);
}
