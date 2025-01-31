/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:49:39 by nrontey           #+#    #+#             */
/*   Updated: 2025/01/31 01:10:56 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_color_ok(t_textures *textures)
{
	int	color_exist;
	int	rgb_valid;

	color_exist = textures->f_r == -1 || textures->f_g == -1 || \
	textures->f_b == -1 || textures->c_r == -1 || \
	textures->c_g == -1 || textures->c_b == -1;
	rgb_valid = textures->f_r < 0 || textures->f_r > 255 || textures->f_g < 0 \
	|| textures->f_g > 255 || textures->f_b < 0 || textures->f_b > 255 || \
	textures->c_r < 0 || textures->c_r > 255 || textures->c_g < 0 \
	|| textures->c_g > 255 || textures->c_b < 0 || textures->c_b > 255;
	return (color_exist || rgb_valid);
}

int	is_texture_ok(t_textures *textures)
{
	int		*temp_fd;
	int		i;
	int		ok_count;

	temp_fd = malloc(sizeof(int) * 4);
	ok_count = 0;
	if (!temp_fd)
		return (1);
	temp_fd[0] = open(textures->no_file, O_RDONLY);
	temp_fd[1] = open(textures->so_file, O_RDONLY);
	temp_fd[2] = open(textures->we_file, O_RDONLY);
	temp_fd[3] = open(textures->ea_file, O_RDONLY);
	i = 0;
	while (i < 4)
	{
		if (temp_fd[i] != -1)
		{
			ok_count++;
			close(temp_fd[i]);
		}
		i++;
	}
	free(temp_fd);
	return (ok_count != 4);
}
