/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:44 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/18 01:07:34 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

int	only_variable_expansions(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '$')
			return (0);
		i++;
	}
	return (1);
}

void	aux_update_env(t_data *data_program,
	t_cmd *last_cmd, int size_args)
{
	t_vars	*tmp;

	tmp = data_program->vars;
	tmp = search_var(data_program, "_");
	if (!tmp)
	{
		tmp = new_var("_", last_cmd->args[size_args - 1], 0);
		if (!tmp)
			return ;
		add_var(data_program, tmp);
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup(last_cmd->args[size_args - 1]);
		if (!tmp->value)
			return ;
	}
}

void	update_env(t_data *data_program)
{
	t_vars	*tmp;
	t_cmd	*last_cmd;
	int		size_cmd;
	int		size_args;

	if (!data_program || !data_program->cmds || !data_program->cmds[0])
		return ;
	if (data_program->last_status != 0)
		return ;
	size_cmd = cmd_array_size(data_program->cmds);
	if (size_cmd == 0)
		return ;
	last_cmd = data_program->cmds[size_cmd - 1];
	if (!last_cmd)
		return ;
	size_args = array_size(last_cmd->args);
	if (size_args == 0)
		return ;
	aux_update_env(data_program, last_cmd, size_args);
}
