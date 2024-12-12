/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 05:51:55 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/12 20:41:05 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_valid_texture(t_textures *textures)
{
	int	is_valid;
	int	ext_ok;

	is_valid = textures->NO_file && textures->SO_file && textures->WE_file \
		&& textures->EA_file && textures->F_ok && textures->C_ok;
	ext_ok = is_valid_ext(textures->NO_file, ".xpm") && \
		is_valid_ext(textures->SO_file, ".xpm") && \
		is_valid_ext(textures->WE_file, ".xpm") && \
		is_valid_ext(textures->EA_file, ".xpm");
	return (is_valid && ext_ok);
}

int	ft_is_player_char(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

int	is_valid_chars(char c)
{
	return (c == '0' || c == '1' || c == 'E'
		|| c == 'W' || c == 'N' || c == 'S'
		|| c == ' ' || c == '\t');
}

int	is_char_valid_walls_space(char c)
{
	return (c == '1' || c == '0');
}

int	is_valid_color(char **colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!colors[i] || (i > 0 && !ft_isnumeric(colors[i])))
			return (0);
		i++;
	}
	return (1);
}
