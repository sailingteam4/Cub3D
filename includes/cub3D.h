/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:42:52 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 07:31:45 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../src/libft/libft.h"
# include "../src/mlx_linux/mlx.h"

# define CUBE_SIZE 64

typedef struct s_textures
{
	char	*NO_file;
	char	*SO_file;
	char	*WE_file;
	char	*EA_file;

	int		F_R;
	int		F_G;
	int		F_B;
	int		F_ok;
	int		C_R;
	int		C_G;
	int		C_B;
	int		C_ok;
}	t_textures;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	*current_position;
	t_vector	*start_position;
	double		rotation;
	int			player_count;
}	t_player;

typedef struct s_map
{
	char				**map;
	char				**map_2d;
	int					map_height;
	int					map_width;
	void				*textures[4];
	struct s_player		*player;
	int					is_player;
}	t_map;

typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	struct s_map		*map;
	struct s_textures	*textures;
	int					n_line_file;
}	t_data;

#include "parsing.h"

#endif