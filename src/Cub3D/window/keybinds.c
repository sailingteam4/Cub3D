/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 04:57:28 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/03 14:51:58 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	exit_mlx(t_data *data)
{
	ft_free_data(data);
	exit(0);
}

void	move_player(t_data *data)
{
	float movement_speed = 0.01f;
	float rotation_speed = 0.03f;
	t_player *player = data->map->player;
	float delta_x_3d = cos(player->rotation) * 5;
	float delta_y_3d = sin(player->rotation) * 5;
	float new_x, new_y;

	if (player->moving_forward)
	{
		new_x = player->current_position->x - player->delta_y * movement_speed;
		new_y = player->current_position->y + player->delta_x * movement_speed;
		if (data->map->map_2d[(int)player->current_position->x][(int)new_y] != '1' &&
			data->map->map_2d[(int)new_x][(int)player->current_position->y] != '1')
		{
			player->current_position->x = new_x;
			player->current_position->y = new_y;
		}
	}
	if (player->moving_backward)
	{
		new_x = player->current_position->x + player->delta_y * movement_speed;
		new_y = player->current_position->y - player->delta_x * movement_speed;
		if (data->map->map_2d[(int)player->current_position->x][(int)new_y] != '1' &&
			data->map->map_2d[(int)new_x][(int)player->current_position->y] != '1')
		{
			player->current_position->x = new_x;
			player->current_position->y = new_y;
		}
	}
	if (player->moving_left)
	{
		new_x = player->current_position->x + delta_x_3d * movement_speed;
		new_y = player->current_position->y + delta_y_3d * movement_speed;
		if (data->map->map_2d[(int)player->current_position->x][(int)new_y] != '1' &&
			data->map->map_2d[(int)new_x][(int)player->current_position->y] != '1')
		{
			player->current_position->x = new_x;
			player->current_position->y = new_y;
		}
	}
	if (player->moving_right)
	{
		new_x = player->current_position->x - delta_x_3d * movement_speed;
		new_y = player->current_position->y - delta_y_3d * movement_speed;
		if (data->map->map_2d[(int)player->current_position->x][(int)new_y] != '1' &&
			data->map->map_2d[(int)new_x][(int)player->current_position->y] != '1')
		{
			player->current_position->x = new_x;
			player->current_position->y = new_y;
		}
	}
	if (player->rotating_left)
	{
		player->rotation -= rotation_speed;
		if (player->rotation < 0)
			player->rotation += 2 * M_PI;
		player->delta_x = cos(player->rotation) * 5;
		player->delta_y = sin(player->rotation) * 5;
	}
	if (player->rotating_right)
	{
		player->rotation += rotation_speed;
		if (player->rotation > 2 * M_PI)
			player->rotation -= 2 * M_PI;
		player->delta_x = cos(player->rotation) * 5;
		player->delta_y = sin(player->rotation) * 5;
	}
	if (player->moving_forward || player->moving_backward || 
		player->moving_left || player->moving_right || 
		player->rotating_left || player->rotating_right)
	{
		update_minimap(data, HEIGHT / 80);
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit_mlx(data);
	if (keycode == 119)  // W
		data->map->player->moving_forward = 1;
	if (keycode == 115)  // S
		data->map->player->moving_backward = 1;
	if (keycode == 97)   // A
		data->map->player->moving_left = 1;
	if (keycode == 100)  // D
		data->map->player->moving_right = 1;
	if (keycode == 65361)  // Left arrow
		data->map->player->rotating_left = 1;
	if (keycode == 65363)  // Right arrow
		data->map->player->rotating_right = 1;
	if (keycode == 109)  // M key
	{
		data->map->minimap_display = !data->map->minimap_display;
		update_minimap(data, HEIGHT / 80);
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)  // W
		data->map->player->moving_forward = 0;
	if (keycode == 115)  // S
		data->map->player->moving_backward = 0;
	if (keycode == 97)   // A
		data->map->player->moving_left = 0;
	if (keycode == 100)  // D
		data->map->player->moving_right = 0;
	if (keycode == 65361)  // Left arrow
		data->map->player->rotating_left = 0;
	if (keycode == 65363)  // Right arrow
		data->map->player->rotating_right = 0;
	return (0);
}

int	close_win(t_data *data)
{
	exit_mlx(data);
	return (0);
}
