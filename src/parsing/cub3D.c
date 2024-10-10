/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:49:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/10/10 05:49:07 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	make_the_window(t_data *data)
{
	(void)data;
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_init_data(data);
	if (!ft_check_file(av[1], ac, data))
	{
		ft_free_data(data);
		return (1);
	}
	if (!make_the_window(data))
	{
		ft_free_data(data);
		return (1);
	}
	ft_free_data(data);
	return (0);
}
