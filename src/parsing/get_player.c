/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 06:11:50 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 06:19:41 by nrontey          ###   ########.fr       */
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
	}
	player->current_position->x = x;
	player->current_position->y = y;
	if (rot == 'N')
		player->rotation = 'N';
	else if (rot == 'S')
		player->rotation = 'S';
	else if (rot == 'W')
		player->rotation = 'W';
	else if (rot == 'E')
		player->rotation = 'E';
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
