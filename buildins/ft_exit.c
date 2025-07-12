/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:03:21 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 18:03:27 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_exit(t_data *data, char **args)
{
	int	status;

	status = data->last_status;
	free_data(data);
	exit(status);
}
