/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:44:43 by tpipi             #+#    #+#             */
/*   Updated: 2024/12/16 23:58:27 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	get_horizontal_value(t_raycast *rc, float angle, float x, float y)
{
	rc->hit = 1;
	if (angle > 0 && angle < 180 * RAD) {
		rc->nearest_y = ((int)y/CUBE_SIZE)*CUBE_SIZE;
		rc->nearest_x = (y - rc->nearest_y) / tan(angle) + x;
		rc->offset_y = -CUBE_SIZE;
		rc->offset_x = -rc->offset_y * -1/tan(angle);
	}
	else if (angle > 180 * RAD && angle < 360 * RAD) {
		rc->nearest_y = ((int)y/CUBE_SIZE)*CUBE_SIZE+CUBE_SIZE;
		rc->nearest_x = (y - rc->nearest_y) / tan(angle) + x;
		rc->offset_y = CUBE_SIZE;
		rc->offset_x = -rc->offset_y * -1/tan(angle);
	}
	else {
		rc->nearest_y = 2147483647;
		rc->nearest_x = 2147483647;
		rc->offset_x = 0;
		rc->offset_y = 0;
		rc->hit = 0;
	}
}

void	get_vertical_value(t_raycast *rc, float angle, float x, float y)
{
	rc->hit = 1;
	if (angle > 90 * RAD && angle < 270 * RAD) {
	    rc->nearest_x = ((int)x/CUBE_SIZE)*CUBE_SIZE;
	    rc->nearest_y = (x - rc->nearest_x) / (1/tan(angle)) + y;
	    rc->offset_x = -CUBE_SIZE;
	    rc->offset_y = rc->offset_x * -tan(angle);
	}
	else if (angle < 90 * RAD || angle > 270 * RAD) {
	    rc->nearest_x = ((int)x/CUBE_SIZE)*CUBE_SIZE+CUBE_SIZE;
	    rc->nearest_y = (x - rc->nearest_x) / (1/tan(angle)) + y;
	    rc->offset_x = CUBE_SIZE;
	    rc->offset_y = rc->offset_x * -tan(angle);
	}
	else {
	    rc->nearest_y = 2147483647;
	    rc->nearest_x = 2147483647;
		rc->offset_x = 0;
		rc->offset_y = 0;
	    rc->hit = 0;
	}
}

void	find_wall(t_raycast *rc, t_map *map)
{
	while (rc->hit) {
		if (rc->nearest_x < 0 || rc->nearest_x >= map->map_width || \
			rc->nearest_y < 0 || rc->nearest_y >= map->map_height)
		{
			rc->nearest_y = 2147483647;
			rc->nearest_x = 2147483647;
			rc->hit = 0;
		} 
		else if (map->map_2d[(int)rc->nearest_y][(int)rc->nearest_x] == '1')
			rc->hit = 0;
		else
		{
			rc->nearest_x+=rc->offset_x;
			rc->nearest_y+=rc->offset_y;
		}
	}
}
#include <stdio.h>

t_raycast ft_raycaster(t_map *map, t_player *player, float angle)
{
	t_raycast	rc;
	float		x;
	float		y;

	x = player->current_position->y;
	y = player->current_position->x;
	get_horizontal_value(&rc, angle, x, y);
	find_wall(&rc, map);
	rc.wall_x = (int)rc.nearest_x;
	rc.wall_y = (int)rc.nearest_y;
	rc.dist = sqrt((rc.nearest_x-x)*(rc.nearest_x-x)+(rc.nearest_y-y)*(rc.nearest_y-y));
	printf("Horizontal Wall Values x:%d y:%d\n", rc.wall_x, rc.wall_y);
	get_vertical_value(&rc, angle, x, y);
	find_wall(&rc, map);
	printf("Vertical Wall Values x:%d y:%d\n", (int)rc.nearest_x, (int)rc.nearest_y);
	if (sqrt((rc.nearest_x-x)*(rc.nearest_x-x)+(rc.nearest_y-y)*(rc.nearest_y-y)) < rc.dist)
	{
		rc.wall_x = (int)rc.nearest_x;
		rc.wall_y = (int)rc.nearest_y;
		rc.dist = sqrt((rc.nearest_x-x)*(rc.nearest_x-x)+(rc.nearest_y-y)*(rc.nearest_y-y));
	}
    return (rc);
}
