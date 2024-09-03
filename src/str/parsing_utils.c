/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:11:02 by nrontey           #+#    #+#             */
/*   Updated: 2024/09/03 20:30:48 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

bool	check_file_name(char *filename)
{
	if ((!filename || ft_strlen(filename) < 4) || (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub")))
	{
		printf("Error\nInvalid file name or extension\n");
		return (false);
	}
	return (true);
}