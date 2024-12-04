/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 04:57:28 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/04 17:24:18 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	exit_mlx(t_data *data)
{
	ft_free_data(data);
	exit(0);
}

static void	handle_forward_movement(t_data *data, t_player *player, float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->current_position->x - player->delta_y * speed;
	new_y = player->current_position->y + player->delta_x * speed;
	if (data->map->map_2d[(int)player->current_position->x][(int)new_y] != '1' \
	&& data->map->map_2d[(int)new_x][(int)player->current_position->y] != '1')
	{
		player->current_position->x = new_x;
		player->current_position->y = new_y;
	}
}

static void	handle_backward_movement(t_data *data, t_player *player, \
	float speed)
{
	float	new_x;
	float	new_y;

	new_x = player->current_position->x + player->delta_y * speed;
	new_y = player->current_position->y - player->delta_x * speed;
	if (data->map->map_2d[(int)player->current_position->x][(int)new_y] != '1' \
	&& data->map->map_2d[(int)new_x][(int)player->current_position->y] != '1')
	{
		player->current_position->x = new_x;
		player->current_position->y = new_y;
	}
}

static void	handle_side_movement(t_data *data, t_player *player, float speed,
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
	if (data->map->map_2d[(int)player->current_position->x][(int)new_y] != '1' \
	&& data->map->map_2d[(int)new_x][(int)player->current_position->y] != '1')
	{
		player->current_position->x = new_x;
		player->current_position->y = new_y;
	}
}

static void	handle_rotation(t_player *player, float speed, int direction)
{
	player->rotation += direction * speed;
	if (player->rotation < 0)
		player->rotation += 2 * M_PI;
	else if (player->rotation > 2 * M_PI)
		player->rotation -= 2 * M_PI;
	player->delta_x = cos(player->rotation) * 5;
	player->delta_y = sin(player->rotation) * 5;
}

void	move_player(t_data *data)
{
	float		movement_speed;
	float		rotation_speed;
	t_player	*player;

	movement_speed = 0.01f;
	rotation_speed = 0.03f;
	player = data->map->player;
	if (player->moving_forward)
		handle_forward_movement(data, player, movement_speed);
	if (player->moving_backward)
		handle_backward_movement(data, player, movement_speed);
	if (player->moving_left)
		handle_side_movement(data, player, movement_speed, -1);
	if (player->moving_right)
		handle_side_movement(data, player, movement_speed, 1);
	if (player->rotating_left)
		handle_rotation(player, rotation_speed, -1);
	if (player->rotating_right)
		handle_rotation(player, rotation_speed, 1);
	if (player->moving_forward || player->moving_backward || \
		player->moving_left || player->moving_right || \
		player->rotating_left || player->rotating_right)
		update_minimap(data, HEIGHT / 80);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit_mlx(data);
	if (keycode == 119)
		data->map->player->moving_forward = 1;
	if (keycode == 115)
		data->map->player->moving_backward = 1;
	if (keycode == 97)
		data->map->player->moving_left = 1;
	if (keycode == 100)
		data->map->player->moving_right = 1;
	if (keycode == 65361)
		data->map->player->rotating_left = 1;
	if (keycode == 65363)
		data->map->player->rotating_right = 1;
	if (keycode == 109)
	{
		data->map->minimap_display = !data->map->minimap_display;
		update_minimap(data, HEIGHT / 80);
	}
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->map->player->moving_forward = 0;
	if (keycode == 115)
		data->map->player->moving_backward = 0;
	if (keycode == 97)
		data->map->player->moving_left = 0;
	if (keycode == 100)
		data->map->player->moving_right = 0;
	if (keycode == 65361)
		data->map->player->rotating_left = 0;
	if (keycode == 65363)
		data->map->player->rotating_right = 0;
	return (0);
}

int	close_win(t_data *data)
{
	exit_mlx(data);
	return (0);
}
