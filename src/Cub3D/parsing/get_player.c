/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:11:50 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/16 00:07:54 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_vector	*ft_set_player_pos(int x, int y, char rot, t_player *player)
{
	t_vector	*pos;

	if (!player->current_position)
	{
		pos = ft_calloc(1, sizeof(t_vector));
		if (!pos)
			return (NULL);
		player->current_position = pos;
		player->player_count = 0;
	}
	player->player_count++;
	player->current_position->x = x;
	player->current_position->y = y;
	if (rot == 'N')
		player->rotation = M_PI / 2;
	else if (rot == 'S')
		player->rotation = 3 * M_PI / 2;
	else if (rot == 'W')
		player->rotation = 0;
	else if (rot == 'E')
		player->rotation = M_PI;
	player->delta_x = cos(player->rotation) * 5;
	player->delta_y = sin(player->rotation) * 5;
	return (player->current_position);
}

void	get_player(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (data->map->map_2d[x])
	{
		y = 0;
		while (data->map->map_2d[x][y])
		{
			if (ft_is_player_char(data->map->map_2d[x][y]))
			{
				ft_set_player_pos(x, y, data->map->map_2d[x][y], \
					data->map->player);
				data->map->is_player = 1;
				data->map->map_2d[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}
