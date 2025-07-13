/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:55:14 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/13 20:37:07 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_vars	*export_new_var(char *arg)
{
	t_vars	*new;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	printf("%s\n", arg);
	name = ft_strdup_set(&arg[i], "=");
	printf("%s\n", name);
	while (arg[i] != '=')
		i++;
	value = ft_strdup(&arg[i + 1]);
	printf("%s\n", value);
	new = new_var(name, value, 1);
	return (new);
}

static bool	valid_name(char *arg)
{
	int		i;
	bool	equal;
	char	*name;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 0;
	name = ft_strdup_set(arg, "=");
	if (ft_isalnum(name[strlen(name) - 1]))
	{
		free(name);
		return (1);
	}
	return (0);
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



int	ft_export(t_data *data, t_vars *vars, char **args)
{
	int		i;
	t_vars	*arg;
	t_vars	*found;

	if (!vars || !args)
		return (ft_putendl_fd("not enough arguments", 2), 0);
	if (array_size(args) == 1)
	{
		sort_and_print(data, vars, args);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!valid_name(args[i]))
			return (ft_putendl_fd("not valid identifier", 2), 1);
		if (!has_equals(args[i]))
		{
			i++;
			continue ;
		}
		arg = export_new_var(args[i]);
		found = search_var(data, arg->name);
		if (found)
		{
			found->is_exportable = 1;
			free_vars(arg);
		}
		else
			add_var(data, arg);
		i++;
	}
	return (0);
}
