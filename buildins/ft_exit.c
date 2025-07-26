/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:03:21 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/26 21:23:10 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_vars(t_vars *vars);

static bool	is_number(char *str)
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

int	ft_exit(t_data *data, char **args)
{
	int	status;

	if (array_size(args) == 1)
		status = data->last_status;
	else if (array_size(args) > 2)
		return (ft_putendl_fd("too many arguments", 2), 1);
	else
	{
		if (!is_number(args[1]))
			return (ft_putendl_fd("numeric argument required", 2), 2);
		status = ft_atoi(args[1]);
	}
	//printf("EXIT STATUS %d\n", status);
	print_vars(data->vars);
	free_data(data);
	exit(status);
}

void	print_vars(t_vars *vars)
{
	while (vars)
	{
		printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
}