/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:42:52 by nrontey           #+#    #+#             */
/*   Updated: 2024/11/30 18:02:55 by nrontey          ###   ########.fr       */
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
# include "../src/mlx_linux/mlx_int.h"

# define CUBE_SIZE 64
# define M_PI 3.14159265358979323846

typedef struct s_textures
{
	char			*NO_file;
	char			*SO_file;
	char			*WE_file;
	char			*EA_file;

	int				F_R;
	int				F_G;
	int				F_B;
	int				F_ok;
	int				C_R;
	int				C_G;
	int				C_B;
	int				C_ok;
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
	double		delta_x;
	double		delta_y;
	int			player_count;
	int			moving_forward;
	int			moving_backward;
	int			moving_left;
	int			moving_right;
	int			rotating_left;
	int			rotating_right;
}	t_player;

typedef struct s_texture {
    void    *img;           // MLX image pointer
    char    *addr;          // Image data address
    int     width;
    int     height;
    int     line_length;    // Length of a line in bytes
} t_texture;

typedef struct s_map
{
	char				**map;
	char				**map_2d;
	int					map_height;
	int					map_width;
	t_texture			*textures[4];  // Changed from t_img to t_texture
	struct s_player		*player;
	int					is_player;
	bool				minimap_display;
}	t_map;

typedef struct s_data
{
	void				*mlx;
	void				*mlx_win;
	t_img				*img;
	struct s_map		*map;
	struct s_textures	*textures;
	int					n_line_file;
}	t_data;

# include "parsing.h"
# include "graphic.h"

#endif