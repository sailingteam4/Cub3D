/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:49:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/09/03 23:35:25 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_init_map(t_map *map)
{
	map->map = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->textures[0] = NULL;
	map->textures[1] = NULL;
	map->textures[2] = NULL;
	map->textures[3] = NULL;
}

int	main(int ac, char **av)
{
	t_map	*map;

	if (!ft_check_file(av[1], ac))
		return (1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	ft_init_map(map);
	return (0);
}
