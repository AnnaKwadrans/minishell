/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:44 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/19 19:09:44 by akwadran         ###   ########.fr       */
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
		// Si algún argumento NO empieza por '$', hay texto literal
		if (args[i][0] != '$')
			return (0);
		i++;
	}
	return (1); // Todos son expansiones
}

int	is_echo_cmd(char **args)
{
	int	i;

	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "echo"))
		return (1);
	return (0); // Solo tiene opciones de echo
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
	size_cmd = cmd_array_size(data_program->cmds);
	if (size_cmd == 0)
		return ;
	last_cmd = data_program->cmds[size_cmd - 1];
	if (!last_cmd)
		return ;
	if (!is_echo_cmd(last_cmd->args) || only_variable_expansions(last_cmd->args))
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

t_vars	**export_vars(t_data *data_program)
{
	t_vars	*tmp;
	t_vars	**exported_vars;
	int		i;

	tmp = data_program->vars;
	i = 0;
	exported_vars = malloc(sizeof(t_vars *)
			* (count_exportable_vars(data_program) + 1));
	if (!exported_vars)
		return (NULL);
	while (tmp)
	{
		if (tmp->is_exportable)
		{
			exported_vars[i] = tmp;
			i++;
		}
		tmp = tmp->next;
	}
	exported_vars[i] = NULL;
	return (exported_vars);
}

t_vars	*new_var(char *name, char *value, int is_exportable)
{
	t_vars	*new;

	new = malloc(sizeof(t_vars));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	new->is_exportable = is_exportable;
	new->next = NULL;
	return (new);
}

void	add_var(t_data *data_program, t_vars *new)
{
	t_vars	*tmp;

	if (!data_program->vars)
	{
		data_program->vars = new;
		return ;
	}
	tmp = data_program->vars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
