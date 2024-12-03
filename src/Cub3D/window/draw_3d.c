/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:53:26 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/03 15:35:51 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void draw_vertical_line(t_data *data, int x, float wall_height, float tex_x, int texture_index)
{
    if (!data || !data->img || x < 0 || x >= data->img->width)
        return;

    int screen_height = data->img->height;
    float wall_start = (screen_height - wall_height) / 2.0f;
    float wall_end = wall_start + wall_height;
    int y;
    t_texture *texture = data->map->textures[texture_index];  // Use the specified texture

    if (!texture || !texture->addr || !texture->img)
    {
        int wall_color = mlx_rgb_to_int(0, 128, 128, 128);
        y = (int)wall_start;
        while (y < (int)wall_end && y < screen_height)
        {
            if (y >= 0)
                mlx_draw_pixel(data->img, x, y, wall_color);
            y++;
        }
        return;
    }

    // ceiling
    y = 0;
    while (y < (int)wall_start && y < screen_height)
    {
        if (y >= 0)
            mlx_draw_pixel(data->img, x, y, mlx_rgb_to_int(0, data->textures->C_R, data->textures->C_G, data->textures->C_B));
        y++;
    }

    // wall
    y = (int)wall_start;
    while (y < (int)wall_end && y < screen_height)
    {
        if (y >= 0)
        {
            // Use floating-point calculations for smoother texture sampling
            float wall_y = (y - wall_start) / wall_height;
            float tex_y_float = wall_y * texture->height;
            int tex_y = (int)tex_y_float;
            
            // Ensure we stay within texture bounds
            tex_y = fmax(0, fmin(tex_y, texture->height - 1));
            
            // Calculate precise texture coordinates
            float tex_x_precise = tex_x * (texture->width - 1);
            int tex_x_int = (int)tex_x_precise;
            
            // Get color from texture with bounds checking
            if (tex_x_int >= 0 && tex_x_int < texture->width &&
                tex_y >= 0 && tex_y < texture->height)
            {
                unsigned char *pixel = (unsigned char *)texture->addr + 
                                     (tex_y * texture->line_length + tex_x_int * 4);
                unsigned int color = *(unsigned int*)pixel;
                mlx_draw_pixel(data->img, x, y, color);
            }
        }
        y++;
    }

    // floor
    while (y < screen_height)
    {
        if (y >= 0)
            mlx_draw_pixel(data->img, x, y, mlx_rgb_to_int(0, data->textures->F_R, data->textures->F_G, data->textures->F_B));
        y++;
    }
}

float get_distance_to_wall(t_data *data, float x, float y, float angle);

void render_3d_view(t_data *data)
{
    float player_x = data->map->player->current_position->y;
    float player_y = data->map->player->current_position->x;
    float fov = M_PI / 3;
    int num_rays = data->img->width;
    float angle_step = fov / num_rays;
    float start_angle = data->map->player->rotation - (fov / 2);
    
    for (int x = 0; x < num_rays; x++)
    {
        float ray_angle = start_angle + (x * angle_step);
        
        // DDA algorithm variables
        float ray_x = player_x;
        float ray_y = player_y;
        float dir_x = cos(-ray_angle);
        float dir_y = sin(-ray_angle);
        
        // Calculate step and initial side distance
        float delta_dist_x = fabs(1.0f / dir_x);
        float delta_dist_y = fabs(1.0f / dir_y);
        
        int map_x = (int)ray_x;
        int map_y = (int)ray_y;
        
        float side_dist_x;
        float side_dist_y;
        int step_x;
        int step_y;
        int hit = 0;
        int side = 0; // 0 for NS wall, 1 for EW wall
        
        // Calculate step direction and initial side distance
        if (dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (ray_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0f - ray_x) * delta_dist_x;
        }
        if (dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (ray_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0f - ray_y) * delta_dist_y;
        }
        
        // DDA
        while (!hit && map_x >= 0 && map_x < data->map->map_width && 
               map_y >= 0 && map_y < data->map->map_height)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            
            if (map_x >= 0 && map_x < data->map->map_width && 
                map_y >= 0 && map_y < data->map->map_height && 
                data->map->map_2d[map_y][map_x] == '1')
                hit = 1;
        }
        
        // After hit detection, determine which texture to use based on orientation
        int texture_index;
        if (side == 0) // Vertical wall hit (East-West)
        {
            if (dir_x > 0) // Looking West, hit East wall
                texture_index = TEXTURE_EA;
            else // Looking East, hit West wall
                texture_index = TEXTURE_WE;
        }
        else // Horizontal wall hit (North-South)
        {
            if (dir_y > 0) // Looking North, hit South wall
                texture_index = TEXTURE_SO;
            else // Looking South, hit North wall
                texture_index = TEXTURE_NO;
        }

        // Calculate proper distance to remove fisheye
        float angle_diff = ray_angle - data->map->player->rotation;
        
        // Normalize angle_diff to be between -PI and PI
        while (angle_diff > M_PI) angle_diff -= 2 * M_PI;
        while (angle_diff < -M_PI) angle_diff += 2 * M_PI;
        
        // Calculate perpendicular wall distance
        float perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - player_x + (1 - step_x) / 2) / dir_x;
        else
            perp_wall_dist = (map_y - player_y + (1 - step_y) / 2) / dir_y;
            
        // Remove fisheye by using cos of the angle difference
        float corrected_dist = perp_wall_dist * cos(angle_diff);
        float wall_height = (data->img->height / corrected_dist) * 0.75;
        
        // Calculate wall X coordinate
        float wall_x;
        if (side == 0)
            wall_x = player_y + perp_wall_dist * dir_y;
        else
            wall_x = player_x + perp_wall_dist * dir_x;
        wall_x -= floor(wall_x);
        
        // Choose texture and x coordinate
        float tex_x = wall_x;
        if ((side == 0 && dir_x > 0) || (side == 1 && dir_y < 0))
            tex_x = 1.0f - tex_x;
        
        // Update draw_vertical_line call to include texture_index
        draw_vertical_line(data, x, wall_height, tex_x, texture_index);
    }
}
