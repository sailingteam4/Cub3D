/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:00 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/12 20:17:49 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// init_struct.c
int		ft_init_textures(t_data *data);
void	ft_init_data(t_data *data);
int		ft_init_map(t_data *data, int *n_line);

// free.c
int		free_tab(char **tab);
void	ft_free_data(t_data *data);

// utils.c
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isnumeric(char *str);
void	ft_copy(char *src, char *dst);
int		is_valid_ext(char *filename);

// is_valid.c
int		is_valid_texture(t_textures *textures);
int		ft_is_player_char(char c);
int		is_valid_chars(char c);
int		is_char_valid_walls_space(char c);
int		is_valid_color(char **colors);

// line.c
char	*get_next_line_trim(int fd);
int		get_line_color(char *str, char mode, t_textures *textures);
size_t	get_max_line(char **map);
int		ft_get_nb_lines(char *filename);

// check_map.c
int		ft_check_chars(char *str);
int		check_map_lines(t_map *map);
int		check_walls_space(char **map, int x, int y);
int		check_map_content(char **map);

// get_texture.c
int		get_line_texture(char *line, t_textures *textures);
int		handle_texture_data(char *line, t_textures *textures);
int		handle_color_data(char *line, t_textures *textures);
int		ft_parsing_texture(int fd, t_data *data, int *n_line);

// get_player.c
t_vector	*ft_set_player_pos(int x, int y, char rot, t_player *player);
void		get_player(t_data *data);

// cehck_color_text.c
int		is_texture_ok(t_textures *textures);
int		is_color_ok(t_textures *textures);

// map_utils.c
void	ft_set_max_space(t_map *map);
void	ft_fill_map(char *old_line, int fd, t_map *map);

// parsing.c
int		ft_check_file(char	*filename, int ac, t_data *data);

#endif