/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:13:17 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/16 00:05:30 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_step_distances(t_ray_casting *rc)
{
	if (rc->dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->ray_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0f - rc->ray_x) * rc->delta_dist_x;
	}
	if (rc->dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->ray_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0f - rc->ray_y) * rc->delta_dist_y;
	}
}

void	calculate_wall_properties(t_ray_casting *rc, t_data *data)
{
	float	perp_wall_dist;
	float	wall_x;
	float	angle_diff;

	perp_wall_dist = calculate_wall_distance(rc);
	angle_diff = normalize_angle_diff(rc->ray_angle - \
		data->map->player->rotation);
	rc->wall_height = (data->img->height / (perp_wall_dist * cos(angle_diff)))
		* 0.75;
	if (rc->side == 0)
		wall_x = rc->ray_y + perp_wall_dist * rc->dir_y;
	else
		wall_x = rc->ray_x + perp_wall_dist * rc->dir_x;
	wall_x -= floor(wall_x);
	rc->tex_x = wall_x;
	rc->texture_index = get_texture_index(rc);
}

int	get_texture_index(t_ray_casting *rc)
{
	if (rc->side == 0)
	{
		if (rc->dir_x > 0)
			return (TEXTURE_EA);
		return (TEXTURE_WE);
	}
	if (rc->dir_y > 0)
		return (TEXTURE_SO);
	return (TEXTURE_NO);
}

void	draw_simple_wall(t_data *data, int x, int wall_start, int wall_end)
{
	int	y;
	int	wall_color;

	wall_color = mlx_rgb_to_int(0, 128, 128, 128);
	y = (int)wall_start;
	while (y < (int)wall_end && y < data->img->height)
	{
		if (y >= 0)
			mlx_draw_pixel(data->img, x, y, wall_color);
		y++;
	}
}

void	init_ray_casting(t_ray_casting *rc, t_data *data, int x)
{
	rc->ray_angle = data->map->player->rotation - (rc->fov / 2)
		+ (x * rc->angle_step);
	rc->ray_x = data->map->player->current_position->y;
	rc->ray_y = data->map->player->current_position->x;
	rc->dir_x = cos(-rc->ray_angle);
	rc->dir_y = sin(-rc->ray_angle);
	rc->delta_dist_x = fabs(1.0f / rc->dir_x);
	rc->delta_dist_y = fabs(1.0f / rc->dir_y);
	rc->map_x = (int)rc->ray_x;
	rc->map_y = (int)rc->ray_y;
	init_step_distances(rc);
}
