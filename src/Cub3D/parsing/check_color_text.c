/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:49:39 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/14 15:49:42 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_color_ok(t_textures *textures)
{
	return (textures->F_R == -1 || textures->F_G == -1 || textures->F_B == -1
		|| textures->C_R == -1 || textures->C_G == -1 || textures->C_B == -1);
}

int	is_texture_ok(t_textures *textures)
{
	int		*temp_fd;
	int		i;

	temp_fd = malloc(sizeof(int) * 4);
	if (!temp_fd)
		return (1);
	temp_fd[0] = open(textures->NO_file, O_RDONLY);
	temp_fd[1] = open(textures->SO_file, O_RDONLY);
	temp_fd[2] = open(textures->WE_file, O_RDONLY);
	temp_fd[3] = open(textures->EA_file, O_RDONLY);
	i = 0;
	while (i < 4)
	{
		if (temp_fd[i] == -1)
		{
			free(temp_fd);
			return (1);
		}
		close(temp_fd[i]);
		i++;
	}
	free(temp_fd);
	return (0);
}
