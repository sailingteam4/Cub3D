/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:49:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/09 16:17:50 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_check_map(t_data *data)
{
	if (data->map->player->player_count != 1)
	{
		printf("Error\nThere should be only one player\n");
		return (0);
	}
	if (is_color_ok(data->textures))
	{
		printf("Error\nProblem with color\n");
		return (0);
	}
	if (is_texture_ok(data->textures))
	{
		printf("Error\nProblem with texture\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_init_data(data);
	if (!ft_check_file(av[1], ac, data))
	{
		ft_free_data(data);
		return (1);
	}
	if (!ft_check_map(data))
	{
		ft_free_data(data);
		return (1);
	}
	if (!make_the_window(data))
	{
		ft_free_data(data);
		return (1);
	}
	ft_free_data(data);
	return (0);
}
