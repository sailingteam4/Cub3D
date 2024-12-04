/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:42:52 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/04 16:47:28 by nrontey          ###   ########.fr       */
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

# define TEXTURE_NO 0  // North texture
# define TEXTURE_SO 1  // South texture
# define TEXTURE_WE 2  // West texture
# define TEXTURE_EA 3  // East texture

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
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     line_length;
} t_texture;

typedef struct s_ray_casting {
	float	fov;
	float	angle_step;
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	float	dir_x;
	float	dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	float	wall_height;
	float	tex_x;
	int		texture_index;
}	t_ray_casting;

typedef struct s_draw_params {
	int		x;
	float	wall_height;
	float	wall_start;
	float	wall_end;
	int		texture_index;
	int		tex_x_int;
}	t_draw_params;

typedef struct s_map
{
	char				**map;
	char				**map_2d;
	int					map_height;
	int					map_width;
	t_texture			*textures[4];
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

void	init_step_distances(t_ray_casting *rc);
void	calculate_wall_properties(t_ray_casting *rc, t_data *data);
void	draw_simple_wall(t_data *data, int x, int wall_start, int wall_end);

# include "parsing.h"
# include "graphic.h"

int	get_texture_index(t_ray_casting *rc);

#endif