/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:44 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/16 19:28:11 by akwadran         ###   ########.fr       */
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

int	is_echo_cmd(char **args)
{
	int	i;

	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "echo"))
		return (1);
	return (0);
}

size_t	cmd_array_size(t_cmd **cmd)
{
	size_t	size;

	size = 0;
	while (cmd[size])
		size++;
	return (size);
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
	size_cmd = array_size(data_program->cmds);
	if (size_cmd == 0)
		return ;
	last_cmd = data_program->cmds[size_cmd - 1];
	if (!last_cmd)
		return ;
	size_args = array_size(last_cmd->args);
	if (size_args == 0)
		return ;
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
