/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 04:57:28 by nrontey           #+#    #+#             */
/*   Updated: 2024/11/27 14:36:52 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	exit_mlx(t_data *data)
{
	ft_free_data(data);
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	float movement_speed = 0.1f;
	float rotation_speed = 0.1f;

	if (keycode == 65307)
		exit_mlx(data);
    if (keycode == 119) // W - Forward
    {
        data->map->player->current_position->x -= data->map->player->delta_y * movement_speed;
        data->map->player->current_position->y += data->map->player->delta_x * movement_speed;
        update_minimap(data, HEIGHT / 80);
    }
    if (keycode == 115) // S - Backward
    {
        data->map->player->current_position->x += data->map->player->delta_y * movement_speed;
        data->map->player->current_position->y -= data->map->player->delta_x * movement_speed;
        update_minimap(data, HEIGHT / 80);
    }
    if (keycode == 97) // A - Strafe left
    {
        data->map->player->current_position->x -= data->map->player->delta_x * movement_speed;
        data->map->player->current_position->y -= data->map->player->delta_y * movement_speed;
        update_minimap(data, HEIGHT / 80);
    }
    if (keycode == 100) // D - Strafe right
    {
        data->map->player->current_position->x += data->map->player->delta_x * movement_speed;
        data->map->player->current_position->y += data->map->player->delta_y * movement_speed;
        update_minimap(data, HEIGHT / 80);
    }
	if (keycode == 65361) // Left arrow
	{
		data->map->player->rotation += rotation_speed;
		if (data->map->player->rotation > 2 * M_PI)
			data->map->player->rotation -= 2 * M_PI;
		data->map->player->delta_x = cos(data->map->player->rotation) * 5;
		data->map->player->delta_y = sin(data->map->player->rotation) * 5;
		update_minimap(data, HEIGHT / 80);
	}
	if (keycode == 65363) // Right arrow
	{
		data->map->player->rotation -= rotation_speed;
		if (data->map->player->rotation < 0)
			data->map->player->rotation += 2 * M_PI;
		data->map->player->delta_x = cos(data->map->player->rotation) * 5;
		data->map->player->delta_y = sin(data->map->player->rotation) * 5;
		update_minimap(data, HEIGHT / 80);
	}
	printf("angle : %f", data->map->player->rotation * 57.2958);
	return (0);
}

int	close_win(t_data *data)
{
	exit_mlx(data);
	return (0);
}
