/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:46:33 by nrontey           #+#    #+#             */
/*   Updated: 2025/01/31 01:11:13 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	handle_forward_movement(t_data *data, t_player *player, float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->current_position->x - player->delta_y * speed;
	new_y = player->current_position->y + player->delta_x * speed;
	if (!check_collision(data, new_x, new_y))
	{
		player->current_position->x = new_x;
		player->current_position->y = new_y;
	}
}

void	handle_backward_movement(t_data *data, t_player *player, \
	float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->current_position->x + player->delta_y * speed;
	new_y = player->current_position->y - player->delta_x * speed;
	if (!check_collision(data, new_x, new_y))
	{
		player->current_position->x = new_x;
		player->current_position->y = new_y;
	}
}

void	handle_side_movement(t_data *data, t_player *player, float speed,
	int direction)
{
	float	delta_x_3d;
	float	delta_y_3d;
	float	new_x;
	float	new_y;

	delta_x_3d = cos(player->rotation) * 5;
	delta_y_3d = sin(player->rotation) * 5;
	new_x = player->current_position->x + (direction * -delta_x_3d * speed);
	new_y = player->current_position->y + (direction * -delta_y_3d * speed);
	if (!check_collision(data, new_x, new_y))
	{
		player->current_position->x = new_x;
		player->current_position->y = new_y;
	}
}

void	handle_rotation(t_player *player, float speed, int direction)
{
	player->rotation += direction * speed;
	if (player->rotation < 0)
		player->rotation += 2 * M_PI;
	else if (player->rotation > 2 * M_PI)
		player->rotation -= 2 * M_PI;
	player->delta_x = cos(player->rotation) * 5;
	player->delta_y = sin(player->rotation) * 5;
}
