/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:03:21 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/13 20:29:34 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	is_number(char *str);

int	ft_exit(t_data *data, char **args)
{
	int	status;

	if (array_size(args) == 1)
		status = data->last_status;
	else 
	{
		if (!is_number(args[1]))
			return (ft_putendl_fd("not a number", 2), 127);
		status = ft_atoi(args[1]);
	}
	free_data(data);
	exit(status);
}

bool	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || str[i] == '-' || str[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}
