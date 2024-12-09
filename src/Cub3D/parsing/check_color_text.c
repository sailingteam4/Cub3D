/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:49:39 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/09 16:49:49 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_color_ok(t_textures *textures)
{
	int	color_exist;
	int	rgb_valid;

	color_exist = textures->F_R == -1 || textures->F_G == -1 || textures->F_B == -1
		|| textures->C_R == -1 || textures->C_G == -1 || textures->C_B == -1;
	rgb_valid = textures->F_R < 0 || textures->F_R > 255 || textures->F_G < 0 || textures->F_G > 255
		|| textures->F_B < 0 || textures->F_B > 255 || textures->C_R < 0 || textures->C_R > 255
		|| textures->C_G < 0 || textures->C_G > 255 || textures->C_B < 0 || textures->C_B > 255;

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
	temp_fd[0] = open(textures->NO_file, O_RDONLY);
	temp_fd[1] = open(textures->SO_file, O_RDONLY);
	temp_fd[2] = open(textures->WE_file, O_RDONLY);
	temp_fd[3] = open(textures->EA_file, O_RDONLY);
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
