/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:00:31 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/24 06:08:05 by nrontey          ###   ########.fr       */
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
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->mlx_win)
	{
		printf("Error\nmlx_new_window failed\n");
		return (0);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		printf("Error\nmlx_new_image failed\n");
		return (0);
	}
	return (1);
}

int	make_the_window(t_data *data)
{
	if (!init_mlx(data))
		return (0);
	put_minimap(data, HEIGHT / 80);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 17, 0, close_win, data);
	mlx_loop(data->mlx);
	return (1);
}
