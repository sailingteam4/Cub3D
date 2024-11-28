#include "../../includes/cub3D.h"

static void draw_vertical_line(t_data *data, int x, float wall_height, int color)
{
    if (!data || !data->img || x < 0 || x >= data->img->width)
        return;

    int screen_height = data->img->height;
    float wall_start = (screen_height - wall_height) / 2.0f;
    float wall_end = wall_start + wall_height;
    int y;
    
    // ceiling
    y = 0;
    while (y < (int)wall_start && y < screen_height)
    {
        if (y >= 0)
            mlx_draw_pixel(data->img, x, y, mlx_rgb_to_int(0, data->textures->C_R, data->textures->C_G, data->textures->C_B));
        y++;
    }

    // remove shit on the top of the walls
    if (wall_start >= 0 && wall_start < screen_height)
    {
        float fraction = wall_start - (int)wall_start;
        if (fraction > 0.0f)
        {
            int blend_color = mlx_rgb_to_int(0,
                (int)(100 * (1 - fraction) + ((color >> 16) & 0xFF) * fraction),
                (int)(100 * (1 - fraction) + ((color >> 8) & 0xFF) * fraction),
                (int)(100 * (1 - fraction) + (color & 0xFF) * fraction)
            );
            mlx_draw_pixel(data->img, x, (int)wall_start, blend_color);
        }
    }

    // wall
    y = (int)wall_start + 1;
    while (y < (int)wall_end && y < screen_height)
    {
        if (y >= 0)
            mlx_draw_pixel(data->img, x, y, color);
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
    int x;

    x = 0;
    while (x < num_rays)
    {
        float ray_angle = start_angle + (x * angle_step);
        float dist = get_distance_to_wall(data, player_x, player_y, ray_angle);
        
        // fisheye
        dist = dist * cos(fabs(ray_angle - data->map->player->rotation));
        
        // wall height
        float wall_height;
        if (dist < 0.1)
            wall_height = data->img->height;
        else
            wall_height = (data->img->height / dist) * 0.5;
        
        // color intensity based on distance
        int color_intensity = (int)(255.0f / (1.0f + dist * 0.7f));
        int wall_color = mlx_rgb_to_int(0, color_intensity, color_intensity, color_intensity);
        
        draw_vertical_line(data, x, wall_height, wall_color);
        x++;
    }
}
