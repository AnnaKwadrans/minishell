/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:53:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 17:54:20 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	rm_first(t_data *data)
{
	t_vars	*temp;

	temp = data->vars;
	data->vars = temp->next;
	temp->next = NULL;
	free_vars(temp);
	temp = NULL;
}

static void	rm_last(t_vars *vars)
{
	t_vars	*temp;

	temp = vars;
	while (vars && vars->next)
	{
		if (!vars->next->next)
		{
			free_vars(vars->next);
			vars->next = NULL;
			return ;
		}
		vars = vars->next;
	}
}

static void	rm_middle(t_vars *vars, char *name)
{
	t_vars	*temp;

	while (vars && vars->next && vars->next->next)
	{
		if (strncmp(vars->next->name, name, ft_strlen(name)) == 0)
		{
			temp = vars->next->next;
			vars->next->next = NULL;
			free_vars(vars->next);
			vars->next = temp;
			return ;
		}
		vars = vars->next;
	}
}

static void	single_unset(char *arg, t_data *data, t_vars *vars)
{
	t_vars	*start;

	start = vars;
	printf("ARG %s\n", arg);
	printf("VAR %s\n", vars->name);
	if (ft_strncmp(arg, vars->name, ft_strlen(arg)) == 0)
	{
		rm_first(data);
		return ;
	}
	while (vars && vars->next && vars->next->next)
	{
		if (ft_strncmp(arg, vars->next->name, ft_strlen(arg)) == 0)
		{
			rm_middle(start, arg);
			return ;
		}
		vars = vars->next;
	}
	if (ft_strncmp(arg, vars->next->name, ft_strlen(arg)) == 0)
		rm_last(start);
}

int	ft_unset(char **args, t_data *data)
{
	int		i;

	if (!data->vars || !args)
		return (ft_putendl_fd("not enough arguments", 2), 0);
	i = 1;
	while (args[i])
	{
		single_unset(args[i], data, data->vars);
		i++;
	}
	return (0);
}
