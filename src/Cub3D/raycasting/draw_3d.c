/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:53:26 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/12 00:59:21 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_ray_casting(t_ray_casting *rc, t_data *data, int x);

static void	draw_ceiling_floor(t_data *data, int x, int wall_start, \
	int wall_end)
{
	int	y;

	y = 0;
	while (y < wall_start && y < data->img->height)
	{
		if (y >= 0)
			mlx_draw_pixel(data->img, x, y, mlx_rgb_to_int(0, \
			data->textures->C_R, data->textures->C_G, data->textures->C_B));
		y++;
	}
	y = wall_end;
	while (y < data->img->height)
	{
		if (y >= 0)
			mlx_draw_pixel(data->img, x, y, mlx_rgb_to_int(0, \
			data->textures->F_R, data->textures->F_G, data->textures->F_B));
		y++;
	}
}

static void	draw_wall_texture(t_data *data, t_draw_params *params,
		t_texture *texture)
{
	int				y;
	float			tex_pos;
	float			step;
	float			original_height;
	unsigned char	*pixel;

	adjust_wall_height(params, data, &original_height);
	step = (float)texture->height / original_height;
	tex_pos = (params->wall_start - (data->img->height - original_height) \
		/ 2.0f) * step;
	y = (int)params->wall_start;
	while (y < params->wall_end && y < data->img->height)
	{
		if (y >= 0 && params->tex_x_int >= 0 && params->tex_x_int < \
			texture->width)
		{
			pixel = (unsigned char *)texture->addr + (get_texture_y(tex_pos,
						texture->height) * texture->line_length
					+ params->tex_x_int * 4);
			mlx_draw_pixel(data->img, params->x, y, *(unsigned int *)pixel);
		}
		tex_pos += step;
		y++;
	}
}

static void	draw_vertical_line(t_data *data, int x, float wall_height,
		t_ray_casting *rc)
{
	t_draw_params	params;
	t_texture		*texture;
	float			tex_x;
	int				texture_index;

	tex_x = rc->tex_x;
	texture_index = rc->texture_index;
	if (!data || !data->img || x < 0 || x >= data->img->width)
		return ;
	params.x = x;
	params.wall_height = wall_height;
	params.wall_start = (data->img->height - wall_height) / 2.0f;
	params.wall_end = params.wall_start + wall_height;
	params.texture_index = texture_index;
	texture = data->map->textures[texture_index];
	if (!texture || !texture->addr || !texture->img)
	{
		draw_simple_wall(data, x, params.wall_start, params.wall_end);
		return ;
	}
	params.tex_x_int = (int)(tex_x * (texture->width - 1));
	draw_ceiling_floor(data, x, params.wall_start, params.wall_end);
	draw_wall_texture(data, &params, texture);
}

static void	perform_dda(t_ray_casting *rc, t_data *data)
{
	rc->hit = 0;
	while (!rc->hit && rc->map_x >= 0 && rc->map_x < data->map->map_width
		&& rc->map_y >= 0 && rc->map_y < data->map->map_height)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (rc->map_x >= 0 && rc->map_x < data->map->map_width
			&& rc->map_y >= 0 && rc->map_y < data->map->map_height
			&& data->map->map_2d[rc->map_y][rc->map_x] == '1')
			rc->hit = 1;
	}
}

void	render_3d_view(t_data *data)
{
	t_ray_casting	rc;
	int				x;

	rc.fov = M_PI / 3;
	rc.angle_step = rc.fov / data->img->width;
	x = 0;
	while (x < data->img->width)
	{
		init_ray_casting(&rc, data, x);
		perform_dda(&rc, data);
		calculate_wall_properties(&rc, data);
		draw_vertical_line(data, x, rc.wall_height, &rc);
		x++;
	}
}
