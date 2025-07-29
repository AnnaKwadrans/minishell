/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:58:53 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 17:59:43 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	pre_env(t_data *data_program)
{
	t_vars	*var;

	if (!data_program || !data_program->vars)
		return ;
	var = search_var(data_program, "_");
	if (var)
	{
		free(var->value);
		var->value = ft_strdup("/usr/bin/env");
	}
	else
	{
		var = new_var("_", "/usr/bin/env", 1);
		var->data = data_program;
		add_var(data_program, var);
	}
}

int	ft_env(t_vars *vars)
{
	if (!vars)
		return (ft_putendl_fd("no vars", 2), -1);
	pre_env(vars->data);
	while (vars)
	{
		if (vars->is_exportable && vars->value[0])
			printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
	return (0);
}
