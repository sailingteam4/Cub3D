/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:01:43 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/16 23:36:40 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HEIGHT 720
#define WIDTH 1040

// keybinds.c
void			exit_mlx(t_data *data);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				close_win(t_data *data);

// mlx_utils.c
unsigned int	mlx_rgb_to_int(int o, int r, int g, int b);
unsigned int	mlx_get_pixel(t_img *img, int x, int y);
void			mlx_draw_pixel(t_img *mlx_img, int x, int y, int color);

// draw_minimap.c
int				update_minimap(t_data *data, int size_modifier);
int				put_minimap(t_data *data, int size_modifier);
void			draw_minimap_tile(t_data *data, int x, int y, int size_modifier);

// mlx_make.c
int				make_the_window(t_data *data);
int				update_minimap(t_data *data, int size_modifier);

// handle_collision.c
void            allocate_check_point(int check_points[4][2], float x, float y);
int             check_collision(t_data *data, float x, float y);

// handle_movement.c
void			handle_forward_movement(t_data *data, t_player *player, float speed);
void			handle_backward_movement(t_data *data, t_player *player, float speed);
void			handle_side_movement(t_data *data, t_player *player, float speed, int direction);
void	        handle_rotation(t_player *player, float speed, int direction);

// draw_utils.c
void			adjust_wall_height(t_draw_params *params, t_data *data,
					float *original_height);
int				get_texture_y(float tex_pos, int texture_height);
float			calculate_wall_distance(t_ray_casting *rc);
float			normalize_angle_diff(float angle_diff);

// draw_player.c
void			draw_player_glow(t_data *data, float px, float py, int radius);
void			draw_player(t_data *data, int x, int y, int size_modifier);

// rc_utils.c
void            init_step_distances(t_ray_casting *rc);
void            calculate_wall_properties(t_ray_casting *rc, t_data *data);
void            draw_simple_wall(t_data *data, int x, int wall_start, int wall_end);
int             get_texture_index(t_ray_casting *rc);