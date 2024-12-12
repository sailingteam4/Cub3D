/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:54:28 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/12 00:56:22 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	allocate_check_point(int check_points[4][2], float x, float y)
{
	check_points[0][0] = (int)(x - COLLISION_BUFFER);
	check_points[0][1] = (int)(y - COLLISION_BUFFER);
	check_points[1][0] = (int)(x - COLLISION_BUFFER);
	check_points[1][1] = (int)(y + COLLISION_BUFFER);
	check_points[2][0] = (int)(x + COLLISION_BUFFER);
	check_points[2][1] = (int)(y - COLLISION_BUFFER);
	check_points[3][0] = (int)(x + COLLISION_BUFFER);
	check_points[3][1] = (int)(y + COLLISION_BUFFER);
}

int	check_collision(t_data *data, float x, float y)
{
	int	check_points[4][2];

	allocate_check_point(check_points, x, y);
	if (check_points[0][0] >= 0 && check_points[0][0] < data->map->map_height
		&& check_points[0][1] >= 0 && check_points[0][1] < data->map->map_width
		&& data->map->map_2d[check_points[0][0]][check_points[0][1]] == '1')
		return (1);
	if (check_points[1][0] >= 0 && check_points[1][0] < data->map->map_height
		&& check_points[1][1] >= 0 && check_points[1][1] < data->map->map_width
		&& data->map->map_2d[check_points[1][0]][check_points[1][1]] == '1')
		return (1);
	if (check_points[2][0] >= 0 && check_points[2][0] < data->map->map_height
		&& check_points[2][1] >= 0 && check_points[2][1] < data->map->map_width
		&& data->map->map_2d[check_points[2][0]][check_points[2][1]] == '1')
		return (1);
	if (check_points[3][0] >= 0 && check_points[3][0] < data->map->map_height
		&& check_points[3][1] >= 0 && check_points[3][1] < data->map->map_width
		&& data->map->map_2d[check_points[3][0]][check_points[3][1]] == '1')
		return (1);
	return (0);
}
