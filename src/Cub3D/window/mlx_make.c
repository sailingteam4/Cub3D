/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:00:31 by nrontey           #+#    #+#             */
/*   Updated: 2024/11/30 18:04:58 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	move_player(t_data *data);

static void	texture_load(t_data *data, t_texture **img, char *path)
{
	int	width;
	int	height;
	int	bpp;
	int	endian;

	if (!path || !data || !data->mlx)
        return;

	(*img) = malloc(sizeof(t_texture));
	if (!(*img))
		return ;
	(*img)->img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if ((*img)->img == NULL)
	{
		free(*img);
		*img = NULL;
		printf("Error: Failed to load texture: %s\n", path);
		return ;
	}
	(*img)->width = width;
	(*img)->height = height;
	(*img)->addr = mlx_get_data_addr((*img)->img, &bpp, &(*img)->line_length, &endian);
	if (!(*img)->addr)
	{
		mlx_destroy_image(data->mlx, (*img)->img);
		free(*img);
		*img = NULL;
		printf("Error: Failed to get texture data address: %s\n", path);
		return;
	}
	printf("Texture loaded successfully: %s (%dx%d)\n", path, width, height);
}

int	open_textures(t_data *data)
{
	int	i;

	texture_load(data, &data->map->textures[0], data->textures->NO_file);
	texture_load(data, &data->map->textures[1], data->textures->SO_file);
	texture_load(data, &data->map->textures[2], data->textures->WE_file);
	texture_load(data, &data->map->textures[3], data->textures->EA_file);
	i = 0;
	while (i < 4)
	{
		if (data->map->textures[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

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
	if (!open_textures(data))
	{
		printf("Error\nopen_textures failed\n");
		return (0);
	}
	return (1);
}

int	game_loop(t_data *data)
{
	move_player(data);
	return (0);
}

int	make_the_window(t_data *data)
{
	if (!init_mlx(data))
		return (0);
	update_minimap(data, HEIGHT / 80);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx_win, 17, 0, close_win, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
	return (1);
}
