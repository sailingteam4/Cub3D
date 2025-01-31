/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:14:28 by nrontey           #+#    #+#             */
/*   Updated: 2025/01/31 01:11:24 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../src/mlx_linux/mlx_int.h"

typedef struct s_textures
{
	char			*no_file;
	char			*so_file;
	char			*we_file;
	char			*ea_file;

	int				f_r;
	int				f_g;
	int				f_b;
	int				f_ok;
	int				c_r;
	int				c_g;
	int				c_b;
	int				c_ok;
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

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		line_length;
}	t_texture;

typedef struct s_ray_casting
{
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

typedef struct s_draw_params
{
	int		x;
	float	wall_height;
	float	wall_start;
	float	wall_end;
	int		texture_index;
	int		tex_x_int;
	float	step;
	float	tex_pos;
	int		img_height;
}	t_draw_params;

typedef struct s_map
{
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

#endif