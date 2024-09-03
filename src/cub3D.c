/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:49:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/09/03 21:25:10 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		printf("Error\nInvalid arguments\nCorrect usage: ./cub3D map.cub\n");
		return (1);
	}
	fd = check_filename(av[1]);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}
