/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:01:43 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/24 06:04:04 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HEIGHT 1080
#define WIDTH 1920

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