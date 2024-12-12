/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:42:52 by nrontey           #+#    #+#             */
/*   Updated: 2024/12/12 01:19:14 by nrontey          ###   ########.fr       */
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
# include "struct.h"
# include "parsing.h"
# include "graphic.h"

# define CUBE_SIZE 1
# define M_PI 3.14159265358979323846
# define RAD 0.0174533
# define COLLISION_BUFFER 0.1f

# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3

#endif