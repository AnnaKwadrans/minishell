/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 00:17:44 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/18 01:07:19 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "varenv.h"

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
