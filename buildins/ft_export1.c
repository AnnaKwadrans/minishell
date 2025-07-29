/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:55:14 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/28 16:16:13 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_vars	*export_new_var(char *arg)
{
	t_vars	*new;
	char	*name;
	char	*value;
	int		i;

	if (!arg)
		return (NULL);
	i = 0;
	name = ft_strdup_set(arg, "=");
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		value = ft_strdup(&arg[i + 1]);
	else
		value = NULL;
	new = new_var(name, value, 1);
	free(name);
	name = NULL;
	if (value)
		free(value);
	value = NULL;
	return (new);
}

static bool	valid_name(char *arg)
{
	int		i;
	bool	equal;
	char	*name;

	if (!arg)
		return (0);
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 0;
	name = ft_strdup_set(arg, "=");
	while (name && name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
		{
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

static bool	has_equals(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	print_vars(t_vars *vars)
{
	while (vars)
	{
		write(2, vars->name, ft_strlen(vars->name));
		write(2, " ", 2);
		write(2, vars->value, ft_strlen(vars->value));
		write(2, "\n", 2);
		vars = vars->next;
	}
}


static int	handle_exp_args(char *arg, t_data *data)
{
	t_vars	*exported;
	t_vars	*found;
	int		i;

	if (!valid_name(arg))
		return (ft_putendl_fd("not a valid identifier", 2), 1);
	//if (!has_equals(arg))
	//	return (ft_putendl_fd("not a valid var", 2), 1);
	exported = export_new_var(arg);
	found = search_var(data, exported->name);
	if (found)
	{
		found->is_exportable = 1;
		free_vars(exported);
	}
	else
		add_var(data, exported);
	return (0);
}

int	ft_export(t_data *data, t_vars *vars, char **args)
{
	int	i;
	int	ret;

	if (!vars || !args)
		return (ft_putendl_fd("not enough arguments", 2), 0);
	if (array_size(args) == 1)
		return (sort_and_print(data, vars, args));
	else
	{
		i = 1;
		while (args && args[i])
		{
			ret = handle_exp_args(args[i], data);
			i++;
		}
	}
	return (ret);
}
