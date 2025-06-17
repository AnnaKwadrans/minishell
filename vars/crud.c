/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:44 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/17 20:39:16 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

static t_cmd	*get_last_cmd(t_data *data_program)
{
	t_cmd	*result;
	int		size;

	if (!data_program->cmds[0])
		return (NULL); // No commands executed yet, nothing to return
	size = array_size(data_program->cmds);
	return (data_program->cmds[size - 1]);
}

void	update_env(t_data *data_program)
{
	t_vars	*tmp;
	t_cmd	*last_cmd;

	// printf("updating \"_\" \n");
	if (!data_program || !data_program->cmds || !data_program->cmds[0])
		return ;
	last_cmd = get_last_cmd(data_program);
	if (!last_cmd)
		return ;
	tmp = search_var(data_program, "_");
	if (!tmp)
	{
		tmp = new_var("_", last_cmd->args[array_size(last_cmd->args) - 1], 0);
		if (!tmp)
			return ;
		add_var(data_program, tmp);
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup(last_cmd->args[array_size(last_cmd->args) - 1]);
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
