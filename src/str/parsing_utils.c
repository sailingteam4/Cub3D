/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:11:02 by nrontey           #+#    #+#             */
/*   Updated: 2024/09/03 20:26:04 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

bool	check_file_name(char *filename)
{
	if (!filename || ft_strlen(filename) < 4)
	{
		printf("Error\nInvalid file name\n");
		return (false);
	}
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub"))
	{
		printf("Error\nInvalid file extension\n");
		return (false);
	}
	return (true);
}