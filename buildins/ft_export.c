/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:55:14 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/13 13:11:48 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	sort_and_print(t_data *data, t_vars *vars, char **args);
void	sort_vars(t_vars *vars);
void	swap_vars(t_vars *vars, t_vars *aux);
void	print_vars(t_vars *vars);
t_vars	*cpy_vars(t_vars *vars);
void	add_cpy_var(t_vars *vars, t_vars *new);

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
		printf("check 1\n");
		sort_and_print(data, vars, args);
		printf("check last\n");
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

void	sort_and_print(t_data *data, t_vars *vars, char **args)
{
	t_vars	*cpy;

	cpy = cpy_vars(vars);
	sort_vars(cpy);
	print_vars(cpy);
	free_vars(cpy);
}

void	sort_vars(t_vars *vars)
{
	t_vars	*aux;
	t_vars	*start;

	start = vars;
	aux = (t_vars *)malloc(sizeof(t_vars));
	if (!aux)
		return ;
	while (vars && vars->next)
	{
		if (ft_strcmp(vars->name, vars->next->name) > 0)
		{
			swap_vars(vars, aux);
			vars = start;
		}
		vars = vars->next;
	}
	free(aux);
}

void	swap_vars(t_vars *vars, t_vars *aux)
{	
	aux->value = vars->value;
	aux->name = vars->name;
	aux->is_exportable = vars->is_exportable;
	vars->name = vars->next->name;
	vars->value = vars->next->value;
	vars->is_exportable = vars->next->is_exportable;
	vars->next->value = aux->value;
	vars->next->name = aux->name;
	vars->next->is_exportable = aux->is_exportable;
}

void	print_vars(t_vars *vars)
{
	while (vars)
	{
		if (vars->is_exportable && ft_strncmp(vars->name, "_", 1) != 0)
			printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
}

t_vars	*cpy_vars(t_vars *vars)
{
	t_vars	*cpy;
	t_vars	*cpy_start;
	t_data	*data_aux;

	cpy_start = new_var(vars->name, vars->value, vars->is_exportable);
	vars = vars->next;
	while (vars)
	{
		//printf ("check cpy\n%s %s %d\n", vars->name, vars->value, vars->is_exportable);
		cpy = new_var(vars->name, vars->value, vars->is_exportable);
		add_cpy_var(cpy_start, cpy);
		vars = vars->next;
	}
	return (cpy_start);
}

void	add_cpy_var(t_vars *vars, t_vars *new)
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
