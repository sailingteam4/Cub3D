/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:00:31 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/14 17:58:34 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error\nmlx_init failed\n");
		return (0);
	}
	data->mlx_win = mlx_new_window(data->mlx, 1080, 720, "cub3D");
	if (!data->mlx_win)
	{
		printf("Error\nmlx_new_window failed\n");
		return (0);
	}
	return (1);
}

int	make_the_window(t_data *data)
{
	if (!init_mlx(data))
		return (0);
	return (1);
}
