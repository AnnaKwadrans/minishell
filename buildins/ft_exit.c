/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:03:21 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/13 13:56:17 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_exit(t_data *data, char **args)
{
	int	status;

	if (array_size(args) == 1)
		status = data->last_status;
	else
		status = ft_atoi(args[1]);
	free_data(data);
	exit(status);
}
