/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:49:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/09/03 20:30:09 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid arguments\nCorrect usage: ./cub3D map.cub\n");
		return (1);
	}
	if (!check_file_name(av[1]))
		return (1);
	return (0);
}
