/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:59:31 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/15 23:21:47 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	adjust_wall_height(t_draw_params *params, t_data *data,
		float *original_height)
{
	const int	max_height = data->img->height * 4;

	*original_height = params->wall_height;
	if (params->wall_height > max_height)
	{
		params->wall_start = (data->img->height - max_height) / 2.0f;
		params->wall_end = params->wall_start + max_height;
		params->wall_height = max_height;
	}
}

int	get_texture_y(float tex_pos, int texture_height)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y >= texture_height)
		tex_y = texture_height - 1;
	if (tex_y < 0)
		tex_y = 0;
	return (tex_y);
}

float	calculate_wall_distance(t_ray_casting *rc)
{
	float	perp_wall_dist;

	if (rc->side == 0)
		perp_wall_dist = (rc->map_x - rc->ray_x + (1 - rc->step_x) / 2)
			/ rc->dir_x;
	else
		perp_wall_dist = (rc->map_y - rc->ray_y + (1 - rc->step_y) / 2)
			/ rc->dir_y;
	return (fmax(perp_wall_dist, 0.1f));
}

float	normalize_angle_diff(float angle_diff)
{
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	return (angle_diff);
}
