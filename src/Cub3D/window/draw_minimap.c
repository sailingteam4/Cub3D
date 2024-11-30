/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:02:59 by nrontey           #+#    #+#             */
/*   Updated: 2024/11/29 23:17:42 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float get_distance_to_wall(t_data *data, float x, float y, float angle)
{
    float ray_x = x;
    float ray_y = y;
    float dir_x = cos(-angle);
    float dir_y = sin(-angle);
    float step = 0.01;

    while (ray_x >= 0 && ray_x < data->map->map_width && 
           ray_y >= 0 && ray_y < data->map->map_height && 
           data->map->map_2d[(int)ray_y][(int)ray_x] != '1')
    {
        ray_x += dir_x * step;
        ray_y += dir_y * step;
    }
    return sqrt((ray_x - x) * (ray_x - x) + (ray_y - y) * (ray_y - y));
}

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
		float fov = M_PI / 3;
		int num_rays = data->img->width;
		float ray_angle;
		float angle_step = fov / num_rays;
		float start_angle = data->map->player->rotation - (fov / 2);
		int ray = 0;

		while (ray < num_rays)
		{
			ray_angle = start_angle + (ray * angle_step);
			float dist = get_distance_to_wall(data, player_x, player_y, ray_angle);
			float dir_x = cos(-ray_angle);
			float dir_y = sin(-ray_angle);
			float line_length = dist * size_modifier;
			float step = 0.5;

			float start_x = x * size_modifier + precise_x;
			float start_y = y * size_modifier + precise_y;
			
			float current_dist = 0;
			while (current_dist < line_length)
			{
				float pixel_x = start_x + (dir_x * current_dist);
				float pixel_y = start_y + (dir_y * current_dist);
				
				if (pixel_x >= 0 && pixel_x < data->img->width &&
					pixel_y >= 0 && pixel_y < data->img->height)
				{
					mlx_draw_pixel(data->img, (int)pixel_x, (int)pixel_y, color);
				}
				current_dist += step;
				}
			ray += 8;
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

void render_3d_view(t_data *data);

int update_minimap(t_data *data, int size_modifier)
{    mlx_clear_window(data->mlx, data->mlx_win);
    
    render_3d_view(data);
    
    if (data->map->minimap_display)
    {
        put_minimap(data, size_modifier);
    }
    
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
    return (1);
}
