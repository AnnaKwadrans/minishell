/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:55:14 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 14:17:23 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	add_cpy_var(t_vars *vars, t_vars *new)
{
	t_vars	*tmp;

	if (!vars)
	{
		vars = new;
		return ;
	}
	tmp = vars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static t_vars	*cpy_vars(t_vars *vars)
{
	t_vars	*cpy;
	t_vars	*cpy_start;
	t_data	*data_aux;

	cpy_start = new_var(vars->name, vars->value, vars->is_exportable);
	vars = vars->next;
	while (vars)
	{
		cpy = new_var(vars->name, vars->value, vars->is_exportable);
		add_cpy_var(cpy_start, cpy);
		vars = vars->next;
	}
	return (cpy_start);
}

static void	swap_vars(t_vars *vars)
{
	char	*aux_name;
	char	*aux_value;
	int		aux_is_exportable;

	aux_value = vars->value;
	aux_name = vars->name;
	aux_is_exportable = vars->is_exportable;
	vars->name = vars->next->name;
	vars->value = vars->next->value;
	vars->is_exportable = vars->next->is_exportable;
	vars->next->value = aux_value;
	vars->next->name = aux_name;
	vars->next->is_exportable = aux_is_exportable;
}

static int	sort_vars(t_vars *vars)
{
	t_vars	*start;
	bool	swapped;

	start = vars;
	while (1)
	{
		swapped = 0;
		while (vars && vars->next)
		{
			if (ft_strcmp(vars->name, vars->next->name) > 0)
			{
				swap_vars(vars);
				swapped = 1;
			}
			vars = vars->next;
		}
		if (!swapped)
			break ;
		vars = start;
	}
	return (0);
}

int	sort_and_print(t_data *data, t_vars *vars, char **args)
{
	t_vars	*cpy;

	cpy = cpy_vars(vars);
	sort_vars(cpy);
	while (cpy)
	{
		if (cpy->is_exportable && ft_strncmp(cpy->name, "_", 1) != 0)
			printf("declare -x %s=\"%s\"\n", cpy->name, cpy->value);
		cpy = cpy->next;
	}
	free_vars(cpy);
	return (0);
}
